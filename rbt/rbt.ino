#include "Ultrasonic.h"
#include <Servo.h>

Servo myServo;

int angle = 0;
float per;
const int m1 = 5;
const int m2 = 6;
const int sens1 = 7;
const int sens2 = 8;

const int phareG = 2;
const int phareD = 3;
//const int objLed = 3;

long RangeInCentimeters1;
long RangeInCentimeters2;

Ultrasonic ultrasonic(4); //commenyt

void piloter() {

}

void Capture() {
  if (RangeInCentimeters1 == 0) {
    Serial.begin("DIVISION PAR 0");
    return;
  }
  per = ((float)(RangeInCentimeters2 - RangeInCentimeters1)/RangeInCentimeters1) *100;

  Serial.print("👓 changement de: ");
  Serial.println(per);

  if (per < 0) {
    Serial.println("HFJZJFGGZF ZUGIB G?NAHGAUIBJFGZG AUGGAGB A2BGY");
  }

}

void MesureDistance() {
  Serial.println("Boucle 1");
  // 1️ Balayage de 0 à 90°
  for (angle = 20; angle <= 160; angle += 20) {
    myServo.write(angle);
    Serial.print("📍 Angle servo: ");
    Serial.println(angle);

    // Optionnel : mesure de distance
    delay(100);
    RangeInCentimeters1 = ultrasonic.MeasureInCentimeters();
    Serial.print("📏 Distance: ");
    Serial.print(RangeInCentimeters1);
    Serial.println(" cm");

    delay(150);
    RangeInCentimeters2 = ultrasonic.MeasureInCentimeters();
    Capture();
  }

  Serial.println("Boucle 2");
  // 2️ Balayage de 90 à 180°  continuation logique
  for (angle = 160; angle >= 20; angle -= 20) {
    myServo.write(angle);
    Serial.print("📍 Angle servo: ");
    Serial.println(angle);

    // Optionnel : mesure de distance
    delay(100);
    RangeInCentimeters1 = ultrasonic.MeasureInCentimeters();
    Serial.print("📏 Distance: ");
    Serial.print(RangeInCentimeters1);
    Serial.println(" cm");
    
    delay(150);
    RangeInCentimeters2 = ultrasonic.MeasureInCentimeters();
    Capture();

  }
}

void setup() {

  myServo.attach(A3);
  Serial.begin(9600);
  Serial.println("✨ Hello World ✨");

  pinMode(phareG, OUTPUT);
  pinMode(phareD, OUTPUT);

  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(sens1, OUTPUT);
  pinMode(sens2, OUTPUT);
//  pinMode(objLed, OUTPUT);

}

void loop() {
  digitalWrite(phareG, HIGH);
  digitalWrite(phareD, HIGH);

  analogWrite(m1, 255);
  analogWrite(m2, 255);
  digitalWrite(sens1, HIGH);
  digitalWrite(sens2, HIGH);

  MesureDistance();
  
}