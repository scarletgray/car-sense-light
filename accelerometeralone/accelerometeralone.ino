// pin constants:
//GND - GND
//VCC - 3.3V
//AREF - 3.3v (shows REF on NANO)
const int xPin = A5;                  // x-axis of the accelerometer
const int yPin = A4;                  // y-axis
const int zPin = A3;                  // z-axis

void setup() {
  // initialize the serial communications:
  Serial.begin(9600);
}

void loop() {
  analogReference(EXTERNAL); //connect 3.3v to AREF
  // print the sensor values:
  // X Reading
  int xValue = (analogRead(xPin));  //maybe later consider subtracting resting value e.g. 512
 // Serial.print("X Value:");
  Serial.print(xValue);
  Serial.print(","); // if want to print a tab between values: "/t"
  // Y Reading
  int yValue = (analogRead(yPin));  // later - 516
//  Serial.print("Y Value:");
  Serial.print(yValue);
  Serial.print(",");
  // Z Reading
  int zValue = (analogRead(zPin));  // later - 624
 // Serial.print("Z Value:");
  Serial.print(zValue);
  Serial.println();
  // delay before next reading:
  delay(100);

  if (xValue < 400) { //Will use x for braking - deceleration  -- need to test these values
    Serial.println("BRAKING");
    delay(300);
  }
  if (yValue > 700) { //Will use y for swerve - acceleration  -- need to test these values
    Serial.println("SWERVING");
    delay(300);
  } 
}
