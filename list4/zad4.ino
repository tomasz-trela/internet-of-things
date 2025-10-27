const int analogPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(analogPin);
  float voltage = sensorValue * (5.0 / 1023.0); 

  Serial.print("ADC: ");
  Serial.print(sensorValue);
  Serial.print("\tVoltage: ");
  Serial.println(voltage);

  delay(100);
}
