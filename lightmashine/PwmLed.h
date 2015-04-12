#ifndef __PWM_LED_H__
#define __PWM_LED_H__

#include "Arduino.h"
#include "Led.h"
#include "constants.h"

class PwmLed: public Led {
  public:
    PwmLed(uint8_t pin);
    void set(uint8_t percent);
    void update();
  private:
    uint8_t _pin;
    uint8_t _oldPercent;
};

#endif
