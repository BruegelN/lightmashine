#ifndef __BACKFIRE_H__
#define __BACKFIRE_H__

#include "Arduino.h"

/*
* Backfire will light up a LED when you go fast from
* by placing this LED in a muffler you got backfire effect.
* On real, turbo charged, cars turbo a simular effect is caused
* by anti-lag system.
*
* It might be cool to support more than one led(=> output pin) later
* to get different color patterns.
*
*/


class Backfire {
  public:
    Backfire(uint8_t pin);
    void checkForActivation(int8_t valuePercentage);

  private:
    const uint8_t _pin;
    // for the old values
    int8_t _history[10];


};

#endif /* __BACKFIRE_H__ */
