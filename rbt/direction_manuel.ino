  int sensorValueX = analogRead(A3);
  int sensorValueY = analogRead(A4);

  Serial.print("X :");
  Serial.print(sensorValueX);
  Serial.print(" | ");
  Serial.print("Y : ");
  Serial.print((sensorValueY));
  Serial.print(" | ");
  Serial.print(digitalRead(bouton));
  Serial.print(" | ");
  Serial.print(digitalRead(SENS_M1));
  Serial.print(" | ");
  Serial.print(digitalRead(SENS_M2));
  Serial.print(" | ");
  Serial.print(digitalRead(VITESSE_M1));
  Serial.print(" | ");
  Serial.println(digitalRead(VITESSE_M2));

  if (sensorValueX < 260) // reculer
  {
    analogWrite(SENS_M1, HIGH);
    analogWrite(SENS_M2, LOW);
    digitalWrite(VITESSE_M1, 255);
    digitalWrite(VITESSE_M2, 255);
  }
  else if (sensorValueX > 750 and sensorValueX < 1023) // avancer
  {
    accelerer();
  }
  else if (sensorValueY > 750) // gauche
  {
    analogWrite(SENS_M1, LOW);
    analogWrite(SENS_M2, HIGH);
    digitalWrite(VITESSE_M1, 255);
    digitalWrite(VITESSE_M2, 0);
  }
  else if (sensorValueY < 260) // droite
  {
    analogWrite(SENS_M1, HIGH);
    analogWrite(SENS_M2, LOW);
    digitalWrite(VITESSE_M1, 0);
    digitalWrite(VITESSE_M2, 255);
  }
  else
  {
    analogWrite(SENS_M1, 0);
    analogWrite(SENS_M2, 0);
    digitalWrite(VITESSE_M1, 0);
    digitalWrite(VITESSE_M2, 0);
  }
