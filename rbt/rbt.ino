#include "Ultrasonic.h"
#include <Servo.h>

Servo sonar_m1;
Servo camera_m1;
Servo camera_m2;

#define ledobj 2
#define leds 3
#define m1 5
#define m2 6
#define sens1 7
#define sens2 8
#define joystick A0


Ultrasonic sonar(4); //Define 

int change = 0;  // Variable de changement de distance
int angle = 0;
long RangeInCentimeters1;
long RangeInCentimeters2;

void pilotage() {

  analogWrite(m1, 255);  // droite
  analogWrite(m2, 255); //gauche 
  digitalWrite(sens1, HIGH); // droite
  digitalWrite(sens2, HIGH); //gauche

}

void Sonar() {
  Serial.println("Boucle 1:");
  for (angle = 20; angle <= 180; angle += 20) {
    sonar_m1.write(angle);
    Serial.print("📍 Angle servo: ");
    Serial.println(angle);

    RangeInCentimeters1 = sonar.MeasureInCentimeters();
    Serial.print("📏 Distance: ");
    Serial.print(RangeInCentimeters1);
    Serial.println(" cm");

    delay(350);
    RangeInCentimeters2 = sonar.MeasureInCentimeters();
  }

  change = (float(RangeInCentimeters2-RangeInCentimeters1)/RangeInCentimeters2);
  if (change < 3.5000000000000) {
    digitalWrite(ledobj, HIGH);

    analogWrite(m1, 0);  // droite
    analogWrite(m2, 0); //gauche 
    digitalWrite(sens1, HIGH); // droite
    digitalWrite(sens2, HIGH); //gauche
  }

  for (angle = 180; angle >= 20; angle -= 20) {
    sonar_m1.write(angle);
    Serial.print("📍 Angle servo: ");
    Serial.println(angle);

    RangeInCentimeters1 = sonar.MeasureInCentimeters();
    Serial.print("📏 Distance: ");
    Serial.print(RangeInCentimeters1);
    Serial.println(" cm");
    
    delay(350);
    RangeInCentimeters2 = sonar.MeasureInCentimeters();
  }

  change = (float(RangeInCentimeters2-RangeInCentimeters1)/RangeInCentimeters2);
  if (change < 3.5000000000000) {
    digitalWrite(ledobj, HIGH);

    analogWrite(m1, 0);  // droite
    analogWrite(m2, 0); //gauche 
    digitalWrite(sens1, HIGH); // droite
    digitalWrite(sens2, HIGH); //gauche
  }
}

void pilotageAlarm() {
  if (angle <= 160 || change == -2) {
    for (int x =0; x < 5; x++) {
      analogWrite(m1, 250);  // droite
      analogWrite(m2, 0); //gauche 
      digitalWrite(sens1, HIGH); // droite
      digitalWrite(sens2, HIGH); //gauche
    }
  }

  if (angle <= 40 || change == -2) {
    for (int x =0; x < 5; x++) {
      analogWrite(m1, 250);  // droite
      analogWrite(m2, 0); //gauche 
      digitalWrite(sens1, HIGH); // droite
      digitalWrite(sens2, HIGH); //gauche
    }
  }

  if (angle >= 40 && angle >= 120 || change == -2) {
    analogWrite(m1, 0);  // droite
    analogWrite(m2, 0); //gauche 
    digitalWrite(sens1, HIGH); // droite
    digitalWrite(sens2, HIGH); //gauche
  }
}

void setup() {
  sonar_m1.attach(A3);
  camera_m1.attach(A2);
  camera_m2.attach(2);

  Serial.begin(9600);

  /*
  * pinMode(leds, OUTPUT);
  */

  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(sens1, OUTPUT);
  pinMode(sens2, OUTPUT);
  pinMode(ledobj, OUTPUT);
  pinMode(joystick, INPUT);

}

void loop() {
  digitalWrite(ledobj, HIGH);
  /* 
  *   digitalWrite(leds, HIGH);
  */

  pilotage();
  Sonar(); 
  delay(200);
}

