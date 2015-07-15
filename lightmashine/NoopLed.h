#ifndef __NOOP_LED_H__
#define __NOOP_LED_H__

#include "Arduino.h"
#include "Led.h"

class NoopLed: public Led {
  public:
    NoopLed(uint8_t pin);
    void set(uint8_t percent);
    void update();
};

#endif
