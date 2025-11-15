#ifndef RgbLedController_h
#define RgbLedController_h

#include "Arduino.h"

class RgbLedController {
  public:
    RgbLedController();
    void init(byte redPin, byte greenPin, byte bluePin);
    void setColor(byte red, byte green, byte blue);
    
    void setRed();
    void setGreen();
    void setBlue();
    void setYellow();
    void setCyan();
    void setMagenta();
    void setWhite();
    void setBlack();

  private:
    byte _redPin;
    byte _greenPin;
    byte _bluePin;
};

#endif