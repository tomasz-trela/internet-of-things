#include <RgbLedController.h>

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3
RgbLedController myLed;

void setup() {
  myLed.init(LED_RED, LED_GREEN, LED_BLUE);
}

void loop() {
  myLed.setRed();
  delay(1000);

  myLed.setGreen();
  delay(1000);

  myLed.setBlue();
  delay(1000);
  
  myLed.setYellow();
  delay(1000);

  myLed.setCyan();
  delay(1000);

  myLed.setMagenta();
  delay(1000);

  myLed.setColor(255, 165, 0);
  delay(1000);

  myLed.setColor(128, 0, 128);
  delay(1000);

  myLed.setBlack();
  delay(1000);
}