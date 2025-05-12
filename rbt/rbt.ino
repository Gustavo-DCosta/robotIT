#include "Ultrasonic.h"
#include <Servo.h>

Servo myServo;

int angle = 0;

const int phareG = 2;
const int phareD = 6;
const int objLed = 3;
const int presence = 8;

Ultrasonic ultrasonic(4);


void setup() {

  myServo.attach(7);

  Serial.begin(9600);
  Serial.println("------------------ ARDUINO STARTED -----------------------------");

  pinMode(phareG, OUTPUT);
  pinMode(phareD, OUTPUT);
  pinMode(objLed, OUTPUT);
  pinMode(presence, INPUT);

}

void loop() {
 long RangeInCentimeters;
 bool state = digitalRead(presence);

 myServo.write(180);

  if (state == 1) {
    digitalWrite(objLed, HIGH);
  }

  Serial.println("The distance to obstacles in front is: ");




  RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval

  Serial.print(RangeInCentimeters); //0~400cm
  Serial.println(" cm");

  digitalWrite(phareG, HIGH);
  digitalWrite(phareD, HIGH);
  delay(400);
}