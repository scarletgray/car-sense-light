#include <Arduino.h>
#include <Math.h>

#include "main.h"

// _______ FUNCTIONAL PROTOTYPES _________
// Functional Prototypes appear in the file where the code is
// but at the front so that the compiler can make 
// placeholders for all the functions it will need
double convertDegreesToRadian(double);
void setupSerial();
void setupGPS();
void setupNRF();
void setupAccelerometer();
double calculateRiderGap(Rider, Rider);
void read_sensors_to_get_self();
void read_other_bike_positions();

    // _______ GLOBAL VARIABLES _________
    // Global variables are ones you want to be able to use through every
    // function. There should only ever need to be a few
    Rider self;
    Rider peloton[MAX_PELOTON];

    // This chunk of information about a single
    // riders details should be wrapped into an struct (in main.h)
    double lat_tx1_rad = convertDegreesToRadian(-33.870768);
    double long_tx1_rad = convertDegreesToRadian(151.264239);
    // This is another riders position defined as the same struct type
    double lat_me_rad = convertDegreesToRadian(-33.870162);
    double long_me_rad = convertDegreesToRadian(151.264249);

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
  // Tis function will be used to set any variable, pins or modes
  // required to set up the Serial Communications
  Serial.begin (9600);
  return;
}
void setupGPS() {
  // Tis function will be used to set any variable, pins or modes
  // required to set up the GPS
  return;
}
void setupNRF() {
  // Tis function will be used to set any variable, pins or modes
  // required to set up the NRF
  return;
}
void setupAccelerometer() { 
    // Tis function will be used to set any variable, pins or modes
    // required to set up the accelerometer
    return; 
}

//*************************
// L O O P
//*************************
void loop() {
    read_sensors_to_get_self();
    // broadcast_self_data_to_other_bikes()
    read_other_bike_positions();

    calculateRiderGap(self, peloton[0]);

    delay(PAUSE_FOR_LOOP);
}

// _______ HELPERS ___________
// Helper functions sit at the end
double convertDegreesToRadian(double degrees) {
  double radians = (degrees * M_PI) / 180;
  return radians;
}

double calculateRiderGap(Rider me, Rider them) {
  double delta_lat = (them.latitude - me.latitude);
  double delta_long = (them.longitude - me.longitude);

  double A = (sin(delta_lat / 2) * sin(delta_lat / 2)) +
             (cos(lat_me_rad) * cos(lat_tx1_rad) * sin(delta_long / 2) *
              sin(delta_long / 2));

  double C = 2 * atan2(sqrt(A), sqrt(1 - A));
  double D = GLOBAL_RADIUS * C;

  return D;
}

void read_sensors_to_get_self(){
    // Ordinarily we would get a lot of this data from various sensor calls.
    // However now we will just set a specific set of values.
    self.latitude = -33.870162;
    self.longitude = 151.264249; 
    self.elevation = 19;
    self.heading = 0;
    self.speed = 0;
    self.accel_x = 0;
    self.accel_y = 0;
    self.is_swerving = false;
    self.is_breaking = false;
    self.name = "Self";
    return;
}

void read_other_bike_positions(){
    for (int loop=0; loop < MAX_PELOTON; loop++){
        String label = "pel_";
        peloton[loop].latitude = -33.870768;
        peloton[loop].longitude = 151.264239;
        peloton[loop].elevation = 19;
        peloton[loop].heading = 0;
        peloton[loop].speed = 0;
        peloton[loop].accel_x = 0;
        peloton[loop].accel_y = 0;
        peloton[loop].is_swerving = false;
        peloton[loop].is_breaking = false;
        peloton[loop].name = label.concat(String(loop));
    }
}