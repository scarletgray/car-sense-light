#include <LiquidCrystal.h> // includes the LiquidCrystal Library

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)

int trigPin1 = 8;
int echoPin1 = 9;

int trigPin2 = 11;
int echoPin2 = 12;

byte carCharacter[] = {
  B00000,
  B01010,
  B11111,
  B10001,
  B11111,
  B01010,
  B00000,
  B00000
};

void setup() {
  Serial.begin (250000);

  lcd.begin(16, 4); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  lcd.clear();
  lcd.createChar(0, carCharacter);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);}


void firstsensor() { // This function is for first sensor.
  float duration1, distance1;
  digitalWrite (trigPin1, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPin1, LOW);
  duration1 = pulseIn (echoPin1, HIGH);
  distance1 = (duration1 / 2) / 29.1;

  Serial.print("1st Sensor: ");
  Serial.print(distance1, 0);
  Serial.print("cm    ");


  if (0 < distance1 && distance1 <= 5) {
    lcd.setCursor(0, 0);
    lcd.write(byte(0));
    lcd.print("   ");
  }
  if (5 < distance1 && distance1 <= 10) {
    lcd.setCursor(0, 0);
    lcd.write(byte(0));
    lcd.setCursor(1, 0);
    lcd.write(byte(0));
    lcd.print("  ");
  }
  if (10 < distance1 && distance1 <= 20) {
    lcd.setCursor(0, 0);
    lcd.write(byte(0));
    lcd.setCursor(1, 0);
    lcd.write(byte(0));
    lcd.setCursor(2, 0);
    lcd.write(byte(0));
    lcd.print(" ");

  }
  if (20 < distance1 && distance1 <= 30) {  // Change the number for long or short distances.
    lcd.setCursor(0, 0);
    lcd.write(byte(0));
    lcd.setCursor(1, 0);
    lcd.write(byte(0));
    lcd.setCursor(2, 0);
    lcd.write(byte(0));
    lcd.setCursor(3, 0);
    lcd.write(byte(0));
  }
  if (distance1 > 30 || distance1 < 0) {
    lcd.setCursor(0, 0);
    lcd.print("no-x ");
  }
}

void secondsensor() { // This function is for second sensor.
  float duration2, distance2;
  digitalWrite (trigPin2, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPin2, LOW);
  duration2 = pulseIn (echoPin2, HIGH);
  distance2 = (duration2 / 2) / 29.1;

  Serial.print("2nd Sensor: ");
  Serial.print(distance2, 0);
  Serial.print("cm    ");

  if (0 < distance2 && distance2 <= 5) {
    lcd.setCursor(0, 2);
    lcd.write(42);
    lcd.print("   ");
  }
  if (5 < distance2 && distance2 <= 10) {
    lcd.setCursor(0, 2);
    //lcd.print("bb  ");
    lcd.write(42);
    lcd.write(42);
    lcd.print("  ");
  }
  if (10 < distance2 && distance2 <= 20) {
    lcd.setCursor(0, 2);
    lcd.write(42);
    lcd.write(42);
    lcd.write(42);
    lcd.print(" ");
  }
  if (20 < distance2 && distance2 <= 30) {
    lcd.setCursor(0, 2);
    lcd.write(42);
    lcd.write(42);
    lcd.write(42);
    lcd.write(42);
  }
  if (distance2 > 30 || distance2 < 0) {
    lcd.setCursor(0, 2);
    lcd.print("no-y ");
  }
}

void loop() {
  Serial.println("\n");
  firstsensor();
  secondsensor();
  delay(5);
}
