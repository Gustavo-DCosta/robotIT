#include <arduino.h>

const int distance_Lat1 = 2;

int distance_m       ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("-------------------------------------------------------");

}

void loop() {
  int distance = analogRead(distance_Lat1);
  Serial.println(distance);
  delay(1000);
  //distance_m = pow((3027.4/distance), 1.2134);
 // Serial.println(distance_m);

  // put your main code here, to run repeatedly:

}
