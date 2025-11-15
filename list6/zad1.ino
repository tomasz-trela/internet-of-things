#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS A1

#define LED_RED 6
#define LED_BLUE 3

const float TEMP_COLD = 18.0;
const float TEMP_HOT = 25.0;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

LiquidCrystal_I2C lcd(0x27, 16, 2);

float tempIn;
float tempOut;

float minTempOut = 1000.0;
float maxTempOut = -1000.0;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  sensors.begin();

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void loop() {
  sensors.requestTemperatures();

  tempOut = sensors.getTempCByIndex(0);
  tempIn = sensors.getTempCByIndex(1);

  if (tempOut > maxTempOut) {
    maxTempOut = tempOut;
  }

  if (tempOut < minTempOut) {
    minTempOut = tempOut;
  }

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("IN:  ");
  lcd.print(tempIn);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("OUT: ");
  lcd.print(tempOut);
  lcd.print((char)223);
  lcd.print("C");

  if (tempOut < TEMP_COLD) {
    setLedColor(0, 255);
  } else if (tempOut > TEMP_HOT) {
    setLedColor(255, 0);
  }
  delay(2000);
}

void setLedColor(int red, int blue) {
  analogWrite(LED_RED, 255 - red);
  analogWrite(LED_BLUE, 255 - blue);
}