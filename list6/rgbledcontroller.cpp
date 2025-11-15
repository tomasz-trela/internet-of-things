#include "Arduino.h"
#include "RgbLedController.h"

RgbLedController::RgbLedController() {
}

void RgbLedController::init(byte redPin, byte greenPin, byte bluePin) {
  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;

  pinMode(_redPin, OUTPUT);
  pinMode(_greenPin, OUTPUT);
  pinMode(_bluePin, OUTPUT);
}

void RgbLedController::setColor(byte red, byte green, byte blue) {
  analogWrite(_redPin, red);
  analogWrite(_greenPin, green);
  analogWrite(_bluePin, blue);
}

void RgbLedController::setRed() {
  setColor(255, 0, 0);
}

void RgbLedController::setGreen() {
  setColor(0, 255, 0);
}

void RgbLedController::setBlue() {
  setColor(0, 0, 255);
}

void RgbLedController::setYellow() {
  setColor(255, 255, 0);
}

void RgbLedController::setCyan() {
  setColor(0, 255, 255);
}

void RgbLedController::setMagenta() {
  setColor(255, 0, 255);
}

void RgbLedController::setWhite() {
  setColor(255, 255, 255);
}

void RgbLedController::setBlack() {
  setColor(0, 0, 0);
}