#define POTENTIOMETER_PIN A0

void setup() {
  Serial.begin(9600);
}

void loop() {
  int adcValue = analogRead(POTENTIOMETER_PIN);
  float voltage = (adcValue / 1023.0) * 5.0;
  
  Serial.println(voltage);

  delay(50);
}