const int m1 = 4;
const int m2 = 5;
const int sens1 = 6;
const int sens2 = 7;


void setup() { // comment
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(sens1, OUTPUT);
  pinMode(sens2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  analogWrite(m1, 255);
  analogWrite(m2, 255);
  digitalWrite(sens1, HIGH);
  digitalWrite(sens2, HIGH);

}
