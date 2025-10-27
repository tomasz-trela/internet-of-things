#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define POTENTIOMETER_PIN A0

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Zadanie 3");
  lcd.setCursor(0, 1);
  lcd.print("Odczyt napiecia");
  delay(2000);
  lcd.clear();
}

void loop() {
  int adcValue = analogRead(POTENTIOMETER_PIN);
  float voltage = (adcValue / 1023.0) * 5.0;

  lcd.setCursor(0, 0);
  lcd.print("Wartosc ADC: ");
  lcd.print(adcValue);
  lcd.print("    ");

  lcd.setCursor(0, 1);
  lcd.print("Napiecie: ");
  lcd.print(voltage, 2);
  lcd.print(" V  ");

  delay(200);
}