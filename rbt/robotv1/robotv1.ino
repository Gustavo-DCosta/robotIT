#include "Ultrasonic.h"
#include <Servo.h>

// Servos
Servo sonar_m1;
Servo camera_X;
Servo camera_Y;

// Pins
#define ledobj 2
#define m1 5
#define m2 6
#define sens1 7
#define sens2 8

Ultrasonic sonar(4); // Ultrasonic

// parametres camera

const int angleStep = 12;     
const int startX = 60;         
const int endX = 120;           
const int baseY = 90;           


// Variables globales
int sensorValueX = analogRead(A3);
int sensorValueY = analogRead(A4);
int angle = 0;
float change = 0;
long RangeInCentimeters1 = 0;
long RangeInCentimeters2 = 0;

void setup() {
  sonar_m1.attach(A0);
  camera_X.attach(A1);
  camera_Y.attach(A2);  

  Serial.begin(9600);

  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(sens1, OUTPUT);
  pinMode(sens2, OUTPUT);
  pinMode(ledobj, OUTPUT);

  camera_X.write(90);
  camera_Y.write(90);

  sonar_m1.write(-90);
  camera_X.write(startX);
  camera_Y.write(baseY);
}

void oscillateY() {
  camera_Y.write(baseY + 18);  // +10%
  delay(300);
  camera_Y.write(baseY - 18);  // -10%
  delay(300);
  camera_Y.write(baseY);       // Retour au centre
  delay(300);
}

void pilotage() {
  analogWrite(m1, 86);  // droite
  analogWrite(m2, 86);  // gauche
  digitalWrite(sens1, HIGH);
  digitalWrite(sens2, HIGH);
}

void arretMotor() {
  analogWrite(m1, 0);
  analogWrite(m2, 0);
  digitalWrite(sens1, HIGH);
  digitalWrite(sens2, HIGH);
  digitalWrite(ledobj, HIGH);
}

void pilotageManuel() {
  if (sensorValueX < 260) // reculer
  {
    analogWrite(m1, HIGH);
    analogWrite(m2, LOW);
    digitalWrite(sens1, LOW);
    digitalWrite(sens2, HIGH);
  }
  else if (sensorValueX > 750 and sensorValueX < 1023) // avancer
  {
    //accelerer();
  }
  else if (sensorValueY > 750) // gauche
  {
    analogWrite(m1, 0);
    analogWrite(m2, 86);
    digitalWrite(sens1, HIGH);
    digitalWrite(sens2, LOW);
  }
  else if (sensorValueY < 260) // droite
  {
    analogWrite(m1, 86);
    analogWrite(m2, 0);
    digitalWrite(sens1, LOW);
    digitalWrite(sens2, HIGH);
  }
  else
  {
    analogWrite(m1, 0);  
    analogWrite(m2, 0);
    digitalWrite(sens1, HIGH);
    digitalWrite(sens2, HIGH);
  }
}

void scanSonar() {
  for (angle = 20; angle <= 180; angle += 20) {
    sonar_m1.write(angle);
    delay(200);
    RangeInCentimeters1 = sonar.MeasureInCentimeters();
    delay(200);
    RangeInCentimeters2 = sonar.MeasureInCentimeters();

    Serial.print("📍 Angle: ");
    Serial.print(angle);
    Serial.print("° | 📏 D1: ");
    Serial.print(RangeInCentimeters1);
    Serial.print(" cm | D2: ");
    Serial.print(RangeInCentimeters2);
    Serial.print(" cm");

    if (RangeInCentimeters2 != 0) {
      change = float(RangeInCentimeters2 - RangeInCentimeters1) / RangeInCentimeters2;
    } else {
      change = 0;
    }

    Serial.print(" | Δ: ");
    Serial.println(change, 3);

    if (abs(change) > 0.3) {
      arretMotor();
    }
  }

  for (angle = 180; angle >= 20; angle -= 20) {
    sonar_m1.write(angle);
    delay(200);
    RangeInCentimeters1 = sonar.MeasureInCentimeters();
    delay(200);
    RangeInCentimeters2 = sonar.MeasureInCentimeters();

    Serial.print("📍 Angle: ");
    Serial.print(angle);
    Serial.print("° | 📏 D1: ");
    Serial.print(RangeInCentimeters1);
    Serial.print(" cm | D2: ");
    Serial.print(RangeInCentimeters2);
    Serial.print(" cm");

    if (RangeInCentimeters2 != 0) {
      change = float(RangeInCentimeters2 - RangeInCentimeters1) / RangeInCentimeters2;
    } else {
      change = 0;
    }

    Serial.print(" | Δ: ");
    Serial.println(change, 3);

    if (abs(change) > 0.3) {
      arretMotor();
    }
  }
}

void pilotageAlarm() {
  if (angle <= 40 || abs(change) > 0.3) { 
  /* Si l'angle est très à gauche ou droie
    * et que la difference est de 0.3 alors il y a quelque chose devant
  */
    for (int x = 0; x < 5; x++) {
      analogWrite(m1, 86);  // tourner un peut
      analogWrite(m2, 0);
      digitalWrite(sens1, HIGH);
      digitalWrite(sens2, HIGH);
    }
  } 
  if (angle >= 120 || abs(change) > 0.3) {
    analogWrite(m1, 86);
    analogWrite(m2, 0);
    digitalWrite(sens1, HIGH);
    digitalWrite(sens2, LOW);
  } else if (angle > 40 && angle < 160) {
    arretMotor();
  }
}

void loop() {
  for (int angleX = startX; angleX <= endX; angleX += angleStep) {
    camera_X.write(angleX);
    delay(300);
    oscillateY();
  }

  // Balayage vers la gauche
  for (int angleX = endX; angleX >= startX; angleX -= angleStep) {
    camera_X.write(angleX);
    delay(300);
    oscillateY();
  }

  analogWrite(m1, 86);
  analogWrite(m2, 86);
  digitalWrite(sens1, HIGH);
  digitalWrite(sens2, HIGH);

  pilotage();
  scanSonar();
  pilotageAlarm();
  pilotageManuel();

  delay(200);

}