#include <LiquidCrystal_I2C.h>
#include <util/atomic.h>

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3
#define ENCODER1 A2
#define ENCODER2 A3
#define SELECT_BUTTON 2
#define DEBOUNCING_PERIOD 100
#define ENCODER_DEBOUNCING 10

LiquidCrystal_I2C lcd(0x27, 16, 2);

volatile bool encoderRotated = false;
volatile bool rotationDirection = false;
volatile bool buttonPressed = false;

int redValue = 0;
int greenValue = 0;
int blueValue = 0;

enum State { STATE_MENU, STATE_EDIT_RED, STATE_EDIT_GREEN, STATE_EDIT_BLUE };
State currentState = STATE_MENU;
int menuCursor = 0;
const int menuItemsCount = 3;
const char* menuItems[] = {"RED", "GREEN ", "BLUE"};

ISR(PCINT1_vect) {
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterruptTime > ENCODER_DEBOUNCING) {
    if (digitalRead(ENCODER1) == LOW) {
      rotationDirection = (digitalRead(ENCODER2) == HIGH);
      encoderRotated = true;
    }
  }
  lastInterruptTime = interruptTime;
}

void button_ISR() {
    static unsigned long lastInterruptTime = 0;
    unsigned long interruptTime = millis();
    if (interruptTime - lastInterruptTime > DEBOUNCING_PERIOD) {
        buttonPressed = true;
    }
    lastInterruptTime = interruptTime;
}

void updateLeds() {
  analogWrite(LED_RED, redValue);
  analogWrite(LED_GREEN, greenValue);
  analogWrite(LED_BLUE, blueValue);
}

void displayMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(menuCursor == 0 ? ">" : " ");
  lcd.print(menuItems[0]);
  lcd.print(":");
  lcd.print(redValue);

  lcd.setCursor(0, 1);
  lcd.print(menuCursor == 1 ? ">" : " ");
  lcd.print(menuItems[1]);
  lcd.print(":");
  lcd.print(greenValue);
  
  if (menuCursor == 2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(menuItems[1]);
    lcd.print(":");
    lcd.print(greenValue);

    lcd.setCursor(0, 1);
    lcd.print(">");
    lcd.print(menuItems[2]);
    lcd.print(":");
    lcd.print(blueValue);
  }
}

void displayEditScreen() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Edit:");
    
    int valueToDisplay = 0;
    switch(currentState) {
        case STATE_EDIT_RED:
            lcd.print(menuItems[0]);
            valueToDisplay = redValue;
            break;
        case STATE_EDIT_GREEN:
            lcd.print(menuItems[1]);
            valueToDisplay = greenValue;
            break;
        case STATE_EDIT_BLUE:
            lcd.print(menuItems[2]);
            valueToDisplay = blueValue;
            break;
        default: break;
    }

    lcd.setCursor(0, 1);
    lcd.print("Value: ");
    lcd.print(valueToDisplay);
}

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  pinMode(ENCODER1, INPUT_PULLUP);
  pinMode(ENCODER2, INPUT_PULLUP);
  pinMode(SELECT_BUTTON, INPUT_PULLUP);

  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << PCINT10);

  attachInterrupt(digitalPinToInterrupt(SELECT_BUTTON), button_ISR, FALLING);

  lcd.init();
  lcd.backlight();
  
  updateLeds();
  displayMenu();
}

void loop() {
  bool needsDisplayUpdate = false;
  
  if (encoderRotated) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      encoderRotated = false;
    }

    if (currentState == STATE_MENU) {
      if (rotationDirection) {
        menuCursor++;
        if (menuCursor >= menuItemsCount) menuCursor = 0;
      } else {
        menuCursor--;
        if (menuCursor < 0) menuCursor = menuItemsCount - 1;
      }
    } else {
      int* valueToEdit = nullptr;
      if (currentState == STATE_EDIT_RED) valueToEdit = &redValue;
      else if (currentState == STATE_EDIT_GREEN) valueToEdit = &greenValue;
      else if (currentState == STATE_EDIT_BLUE) valueToEdit = &blueValue;

      if (valueToEdit) {
        if (rotationDirection) {
          *valueToEdit += 5;
          if (*valueToEdit > 255) *valueToEdit = 255;
        } else {
          *valueToEdit -= 5;
          if (*valueToEdit < 0) *valueToEdit = 0;
        }
        updateLeds();
      }
    }
    needsDisplayUpdate = true;
  }

  if (buttonPressed) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      buttonPressed = false;
    }

    if (currentState == STATE_MENU) {
      if (menuCursor == 0) currentState = STATE_EDIT_RED;
      else if (menuCursor == 1) currentState = STATE_EDIT_GREEN;
      else if (menuCursor == 2) currentState = STATE_EDIT_BLUE;
    } else {
      currentState = STATE_MENU;
    }
    needsDisplayUpdate = true;
  }

  if (needsDisplayUpdate) {
    if (currentState == STATE_MENU) {
      displayMenu();
    } else {
      displayEditScreen();
    }
  }
}
