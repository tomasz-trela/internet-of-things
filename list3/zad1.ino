#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

#define DEBOUNCE_DELAY 50

int leds[] = {LED_RED, LED_GREEN, LED_BLUE};
int led_index = 0;

int greenButtonState;
int lastGreenButtonState = HIGH;
int redButtonState;
int lastRedButtonState = HIGH;

unsigned long lastDebounceTime = 0;

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);

  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_RED, HIGH);
}

void loop() {
  handleButtonPress(GREEN_BUTTON, greenButtonState, lastGreenButtonState);
  handleButtonPress(RED_BUTTON, redButtonState, lastRedButtonState);
}

void handleButtonPress(int buttonPin, int &buttonState, int &lastButtonState) {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        changeLedColor();
      }
    }
  }

  lastButtonState = reading;
}

void changeLedColor() {
  digitalWrite(leds[led_index], LOW);
  
  led_index = (led_index + 1) % 3;
  
  digitalWrite(leds[led_index], HIGH);
}