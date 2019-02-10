#include <Arduino.h>
#include <ArduinoJson.h>
#include <Math.h>

#include "main.h"

// _______ FUNCTIONAL PROTOTYPES _________
// Functional Prototypes appear in the file where the code is
// but at the front so that the compiler can make
// placeholders for all the functions it will need
double deg2rad(double);
void setupSerial();
void setupGPS();
void setupNRF();
void setupAccelerometer();
double calculateRiderGap(Rider, Rider);
void read_sensors_to_get_self();
void read_other_bike_positions();
void output_distance(int, double);
void broadcast_self_data_to_other_bikes();
void send_rider_json(Rider, String);
String create_rider_json(Rider, bool);
void output_rider(Rider);
String nrf_read_data_channel(byte[]);

    // _______ GLOBAL VARIABLES _________
    // Global variables are ones you want to be able to use through every
    // function. There should only ever need to be a few
    Rider self;
Rider peloton[MAX_PELOTON];

//*************************
// S E T U P
//*************************
void setup() {
  // Set up the program in stages based on atomised code chunks
  setupSerial();
  setupGPS();
  setupNRF();
  setupAccelerometer();
}

void setupSerial() {
  // This function will be used to set any variable, pins or modes
  // required to set up the Serial Communications

  Serial.begin(115200);
  return;
}
void setupGPS() {
  // This function will be used to set any variable, pins or modes
  // required to set up the GPS

  // TODO: eveything
  return;
}
void setupNRF() {
  // This function will be used to set any variable, pins or modes
  // required to set up the NRF

  // TODO: eveything
  return;
}
void setupAccelerometer() {
  // This function will be used to set any variable, pins or modes
  // required to set up the accelerometer

  // TODO: eveything
  return;
}

//*************************
// L O O P
//*************************
void loop() {
  // DATA HANDLING/INPUT
  read_sensors_to_get_self();
  broadcast_self_data_to_other_bikes();
  read_other_bike_positions();

  // DATA PROCESSING
  for (int loop = 0; loop < MAX_PELOTON; loop++) {
    // variable defined here are only valid for each pass through the loop
    double gap;
    gap = calculateRiderGap(self, peloton[loop]);
    output_distance(loop, gap);
  }

  //DATA OUTPUT

  // OTHER
  delay(PAUSE_FOR_LOOP);
}

// _______ OUTPUT ___________
void output_distance(int count, double value) {
  // Simple function to format [rider, distance] for printing
  Serial.print("Gap to rider ");
  Serial.print(String(count));
  Serial.print(" is ");
  Serial.print(value);
  Serial.println("m");
}

void output_rider(Rider rider) {
  // print the rider JSON out to serial output
  String output = create_rider_json(rider, true);
  Serial.print(output);
  return;
}

// _______ HELPERS ___________
// Helper functions sit at the end
double deg2rad(double degrees) {
  // This function coverts degrees to radians as type double
  double radians = (degrees * M_PI) / 180;
  return radians;
}

double calculateRiderGap(Rider me, Rider them) {
  // this function is passed 2 Rider structs
  // It uses the latitude and longitude data therein
  // to determine linear distance based on calculations from
  // [ref:]  http://what_is_that_website?.com

  double delta_lat = (deg2rad(them.latitude) - deg2rad(me.latitude));
  double delta_long = (deg2rad(them.longitude) - deg2rad(me.longitude));

  double A = (sin(delta_lat / 2) * sin(delta_lat / 2)) +
             (cos(deg2rad(me.latitude)) * cos(deg2rad(them.latitude)) * sin(delta_long / 2) *
              sin(delta_long / 2));

  double C = 2 * atan2(sqrt(A), sqrt(1 - A));
  double D = GLOBAL_RADIUS * C;

  return D;
}

void read_sensors_to_get_self() {
  // Ordinarily we would get a lot of this data from various sensor calls.
  // However now we will just set a specific set of values.

  // From GPS
  self.latitude = -33.870162;
  self.longitude = 151.264249;
  self.elevation = 19;

  // From GPS or accel based compass
  self.heading = 0;
  self.speed = 0;

  // from accelerometer
  self.accel_x = 0;
  self.accel_y = 0;

  // derived from accel data and THRESHOLDs in main.h
  self.is_swerving = false;
  self.is_breaking = false;
  self.name = "Self";
  return;
}

void read_other_bike_positions() {
  // We are going to be using data that the bikes pass around to update
  // information for each bike as it is received as JSON string
  for (int loop = 0; loop < MAX_PELOTON; loop++) {
    // TODO: for each rider in peloton
    // first get its address from the struct
    // address = peloton[loop].address
    // then read the NRF channel for that address until you get its JSON
    // String read_json = nrf_read_data_channel(address);
    // then parse that JSON into the peloton Rider array.
    // load_json_to_rider(peloton[loop], read_json);

    // but for now, just loop through the peloton
    // and set them all to the same thing
    String label = "pel_";
    peloton[loop].name = label.concat(String(loop));
    peloton[loop].latitude = -33.870768;
    peloton[loop].longitude = 151.264239;
    peloton[loop].elevation = 19;
    peloton[loop].heading = 0;
    peloton[loop].speed = 0;
    peloton[loop].accel_x = 0;
    peloton[loop].accel_y = 0;
    peloton[loop].is_swerving = false;
    peloton[loop].is_breaking = false;
    // TODO : have a think about what other quantities
    //        might need to go into Rider struct
  }
}


void broadcast_self_data_to_other_bikes(){
  // turn Rider self into JSON packet
  // and then broadcast that information to each bike in peloton
  String self_as_json = create_rider_json(self, false);
  for (int loop=0; loop< MAX_PELOTON; loop++){
    send_rider_json(peloton[loop], self_as_json);
  }
  return;
}

String create_rider_json(Rider rider, bool pretty){
  // this function needs to build a JSON formated String
  // with our representation of the Rider struct
  // input: Rider rider  - the rider to be turned into JSON
  //        bool pretty - use JSON pretty formatting or not
  DynamicJsonBuffer jsonBuffer(512);
  JsonObject &root = jsonBuffer.createObject();
  String result;

  // add the data into root
  // NB using F("string") to push memory usage
  // into stack memory and out of heap memory
  // ... helps program size and speed.
  root[F("latitude")] = rider.latitude;
  root[F("longitude")] = rider.longitude;
  root[F("elevation")] = rider.elevation;
  root[F("heading")] = rider.heading;
  root[F("speed")] = rider.speed;
  root[F("accel_x")] = rider.accel_x;
  root[F("accel_y")] = rider.accel_y;
  root[F("is_swerving")] = rider.is_swerving;
  root[F("is_breaking")] = rider.is_breaking;
  root[F("name")] = rider.name;
  root[F("address")] = rider.address;

  // create the String
  if (pretty)
    root.prettyPrintTo(result);
  else
    root.printTo(result);

  return result;
}

void send_rider_json(Rider destination, String message){
  // This uses the passed destination Rider struct to 
  // get the target bike address or name
  // and then send the message String to that address via NRF

  // TODO: all of it.
  return;
}

void load_json_to_rider(Rider rider, String json_in){
  // This function takes a Rider struct and q JSON formatted string
  // It then breaks the JSON up by keys and inserts the values
  // into the passed Rider struct
  DynamicJsonBuffer serial_json_buffer;
  JsonObject &json_root = serial_json_buffer.parseObject(json_in);
  if (json_root.success()){
    JsonVariant latitude_json = json_root[F("latitude")];
    if (latitude_json.success()) rider.latitude= latitude_json.as<double>();
    JsonVariant longitude_json = json_root[F("longitude")];
    if (longitude_json.success()) rider.longitude= longitude_json.as<double>();
    JsonVariant elevation_json = json_root[F("elevation")];
    if (elevation_json.success()) rider.elevation= elevation_json.as<double>();
    JsonVariant heading_json = json_root[F("heading")];
    if (heading_json.success()) rider.heading= heading_json.as<double>();
    JsonVariant speed_json = json_root[F("speed")];
    if (speed_json.success()) rider.speed= speed_json.as<double>();
    JsonVariant accel_x_json = json_root[F("accel_x")];
    if (accel_x_json.success()) rider.accel_x= accel_x_json.as<double>();
    JsonVariant accel_y_json = json_root[F("accel_y")];
    if (accel_y_json.success()) rider.accel_y= accel_y_json.as<double>();
    JsonVariant is_swerving_json = json_root[F("is_swerving")];
    if (is_swerving_json.success()) rider.is_swerving= is_swerving_json.as<bool>();
    JsonVariant is_breaking_json = json_root[F("is_breaking")];
    if (is_breaking_json.success()) rider.is_breaking= is_breaking_json.as<bool>();
    JsonVariant name_json = json_root[F("name")];
    if (name_json.success()) rider.name= name_json.as<String>();
    JsonVariant address_json = json_root[F("address")];
    if (address_json.success()) rider.address= address_json.as<String>();
  }

  return;
}