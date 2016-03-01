#ifndef __BACKFIRE_H__
#define __BACKFIRE_H__

#include "Arduino.h"

/*
* Backfire will light up a LED's when you go fast from
* by placing this LED in a muffler you got backfire effect.
* On real, turbo charged, cars turbo a simular effect is caused
* by anti-lag system.
*
* To support more than one pin
* an array of pins and the size of the array is needed.
*/


class Backfire {
  public:
    Backfire(const uint8_t *pBackfireArray, const uint8_t backfireLedCount, const uint8_t startBackfire);
    void checkForActivation(int8_t valuePercentage);

  private:
    const uint8_t *_pBackfireArray;
    const uint8_t _backfireLedCount;
    const uint8_t _startBackfire;
    // for the old values
    int8_t _history[10];
    uint8_t _firstLed;



};

#endif /* __BACKFIRE_H__ */
