const int redButtonPin = 2;
const int greenButtonPin = 4;

void setup() {
  Serial.begin(9600);

  pinMode(redButtonPin, INPUT_PULLUP);
  pinMode(greenButtonPin, INPUT_PULLUP);
}

void loop() {
  int redButtonState = !digitalRead(redButtonPin);
  int greenButtonState = !digitalRead(greenButtonPin);

  Serial.print(redButtonState);
  Serial.print(" ");
  Serial.println(greenButtonState);

  delay(10);
}