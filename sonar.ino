#include "Ultrasonic.h"
#include <Servo.h>

Servo myServo;
Ultrasonic ultrasonic(4);

void setup() {
  myServo.attach(8);
  Serial.begin(9600);
  Serial.println("✨ Hello World ✨");
}

void loop() {
  long RangeInCentimeters;
  int angle;

  // 1️⃣ Balayage de 0 à 90°
  for (angle = 0; angle <= 90; angle += 15) {
    myServo.write(angle);
    Serial.print("📍 Angle servo: ");
    Serial.println(angle);

    // Optionnel : mesure de distance
    /*
    RangeInCentimeters = ultrasonic.MeasureInCentimeters();
    Serial.print("📏 Distance: ");
    Serial.print(RangeInCentimeters);
    Serial.println(" cm");
    */

    delay(500); // petit temps pour laisser le servo bouger
  }

  // 2️⃣ Balayage de 90 à 180° ➡️ continuation logique
  for (angle = 105; angle <= 180; angle += 15) {
    myServo.write(angle);
    Serial.print("📍 Angle servo: ");
    Serial.println(angle);

    delay(500);
  }

  Serial.println("✅ Scan terminé. Pause 5 secondes...");
  delay(5000); // petite pause avant de recommencer le loop
}
