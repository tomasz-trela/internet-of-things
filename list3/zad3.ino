#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define RED_BUTTON 2
#define GREEN_BUTTON 4

#define DEBOUNCE_DELAY 50

bool isRunning = false;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
unsigned long lastDisplayUpdateTime = 0;

struct Button {
  const int pin;
  int lastState;
  unsigned long lastDebounceTime;
};

Button greenButton = {GREEN_BUTTON, HIGH, 0};
Button redButton = {RED_BUTTON, HIGH, 0};

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();

  pinMode(greenButton.pin, INPUT_PULLUP);
  pinMode(redButton.pin, INPUT_PULLUP);

  updateDisplay();
}

void loop() {
  handleButtons();

  if (isRunning && (millis() - lastDisplayUpdateTime > 1000)) {
    lastDisplayUpdateTime = millis();
    updateDisplay();
  }
}

bool isButtonPressed(Button &b) {
  int reading = digitalRead(b.pin);

  if (reading != b.lastState) {
    b.lastDebounceTime = millis();
  }

  b.lastState = reading;

  if ((millis() - b.lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading == LOW) {
      return true;
    }
  }
  return false;
}

void handleButtons() {
  if (isButtonPressed(greenButton)) {
    if (isRunning) { 
      elapsedTime += millis() - startTime; 
      isRunning = false;
    } else { 
      startTime = millis();
      isRunning = true;
    }
    while(isButtonPressed(greenButton));
  }

  if (isButtonPressed(redButton)) {
    isRunning = false;
    elapsedTime = 0;
    startTime = millis(); 
    updateDisplay(); 
    while(isButtonPressed(redButton));
  }
}

void updateDisplay() {
  unsigned long timeToDisplay = elapsedTime;
  if (isRunning) {
    timeToDisplay += millis() - startTime;
  }

  int minutes = (timeToDisplay / 60000);
  int seconds = (timeToDisplay / 1000) % 60;
  int tenths = (timeToDisplay / 100) % 10;

  lcd.setCursor(0, 0);
  lcd.print("Stoper:         ");
  lcd.setCursor(0, 1);
  
  char timeBuffer[17];
  sprintf(timeBuffer, "%02d:%02d.%d", minutes, seconds, tenths);
  
  lcd.print(timeBuffer);
}