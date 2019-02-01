#include <Math.h>
#include <Arduino.h>

//int PI = 3.14159265; //may try later with actual set pi from library --> M_PI
int DEG_2_RAD = 180/M_PI; //Conversion from degrees to radians, divide degrees by this

//For testing purposes without transceivers, will set transmitter as centre of Lyne park dog field (-33.870768,151.264239)
int LAT_TX1_RAD = -33.870768/DEG_2_RAD;         //GPS.latitudeDegreesTx/DEG_2_RAD //for testing input values this is from the trasmitting rider
int LONG_TX1_RAD = 151.264239/DEG_2_RAD;        //GPS.longitudeDegreesTx/DEG_2_RAD  
int HEAD_TX1_RAD = (40/DEG_2_RAD)+ 2*M_PI; //Transmitter heading - preset values for testing purposes //adding 2Pi to remove -tve values and values outside range

//For testing purposes, using another point in Lyne park (-33.870162,151.264249)
int LAT_ME_RAD = -33.870162/DEG_2_RAD; //GPS.latitudeDegrees/DEG_2_RAD; //this is the latitude from "Me" the receiving rider from which i will compare the transmitted values
int LONG_ME_RAD = 151.264249/DEG_2_RAD; //GPS.longitudeDegrees/DEG_2_RAD; //this is the longitude from "Me" the receiving rider from which i will compare the transmitted values

int R = 6371e3; //metres
int CHANGE_LAT = (LAT_TX1_RAD-LAT_ME_RAD);
int CHANGE_LONG = (LONG_TX1_RAD-LONG_ME_RAD);

int A = sinf(CHANGE_LAT/2)*sinf(CHANGE_LAT/2) + cosf(LAT_ME_RAD)*cosf(LAT_TX1_RAD)*sinf(CHANGE_LONG/2)*sinf(CHANGE_LONG/2);
int C = 2*atan2f(sqrtf(A),sqrtf(1-A));
int D = R*C;

void setup() {
  // put your setup code here, to run once:
Serial.begin (9600) ;

}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print("--> Distance value =");   //problem atm
Serial.print(D);
Serial.println(", ");
delay(100);
}
