#include "Ultrasonic.h"
#include <Servo.h>

Servo myServo;
Ultrasonic ultrasonic(4);

void setup() {
  myServo.attach(8); // comment
  Serial.begin(9600);
  Serial.println("✨ Hello World ✨");
}

void loop() {
  long RangeInCentimeters;
  int angle;

  // 1️⃣ Balayage de 0 à 90°
  for (angle = 20; angle <= 160; angle += 20) {
    myServo.write(angle);
    Serial.print("📍 Angle servo: ");
    Serial.println(angle);

    // Optionnel : mesure de distance
    delay(300);
    RangeInCentimeters = ultrasonic.MeasureInCentimeters();
    Serial.print("📏 Distance: ");
    Serial.print(RangeInCentimeters);
    Serial.println(" cm");
  }

  // 2️⃣ Balayage de 90 à 180° ➡️ continuation logique
  for (angle = 160; angle >= 20; angle -= 20) {
    myServo.write(angle);
    Serial.print("📍 Angle servo: ");
    Serial.println(angle);

    // Optionnel : mesure de distance
    delay(300);
    RangeInCentimeters = ultrasonic.MeasureInCentimeters();
    Serial.print("📏 Distance: ");
    Serial.print(RangeInCentimeters);
    Serial.println(" cm");
    
  }

  //Serial.println("✅ Scan terminé. Pause 5 secondes...");// petite pause avant de recommencer le loop
  delay(500);
}
