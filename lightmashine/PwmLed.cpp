#include "PwmLed.h"

PwmLed::PwmLed(uint8_t pin) {
   _pin = pin;
   pinMode(pin, OUTPUT);
   _oldPercent = 255; // set wrong value, so set() will do work
   set(0);
}

void PwmLed::set(uint8_t percent) {
  if (percent == _) percent = 0;
  if (percent == X) percent = 100;
  if (percent > 100) percent = 100;
  
  if (percent != _oldPercent) {
    analogWrite(_pin, map(percent, 0, 100, 0, 255));
    _oldPercent = percent;
  }
}

void PwmLed::update() {
}
