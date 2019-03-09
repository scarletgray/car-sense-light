// #include <Arduino.h>
// //#include <ArduinoJson.h>
// #include <Math.h>

// //#include "main.h"

// float deg2rad = M_PI/180; //Conversion from degrees to radians, divide degrees by this

// //For testing purposes without transceivers, will set transmitter as centre of Lyne park dog field (-33.870768,151.264239)
// float lat_transmitter = -33.870768*deg2rad;         //GPS.latitudeDegreesTx*deg2rad //for testing input values this is from the trasmitting rider
// float long_transmitter = 151.264239*deg2rad;        //GPS.longitudeDegreesTx*deg2rad  
// float heading_transmitter = (40*deg2rad)+ 2*M_PI; //Transmitter heading - preset values for testing purposes //adding 2Pi to remove -tve values and values outside range

// //For testing purposes, using another point in Lyne park (-33.870162,151.264249)
// float lat_me = -33.870162*deg2rad; //GPS.latitudeDegrees*deg2rad; //this is the latitude from "Me" the receiving rider from which i will compare the transmitted values
// float long_me = 151.264249*deg2rad; //GPS.longitudeDegrees*deg2rad; //this is the longitude from "Me" the receiving rider from which i will compare the transmitted values
// float R = 6371e3; // earth radius - kilometers to metres

// void setup() {
//   // put your setup code here, to run once:
// i am ruprickt the monkeyboy Serial.begin (9600) ;

// }

// void loop() {
//   // distace calculation - equirectangular approximation:
//   float x = (long_me - long_transmitter) * cosf((lat_transmitter + lat_me)/2);
//   float y = (lat_me - lat_transmitter);
//   float distance_transmitter_me = sqrtf(x*x + y*y) * R;
  
//   Serial.print("--> Distance value =");
//   Serial.print(distance_transmitter_me);
//   Serial.println("metres");
//   delay(100);
// }
