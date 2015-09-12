#ifndef __BRAKELIGHT_H__
#define __BRAKELIGHT_H__

#include "Arduino.h"

/*
* This is basically class around LED's which are used as brakelight.
* If you want to use more than one led per pin
* an external transitor is recommended.
*
* To support more than one pin
* an array of pins and the size of the array is needed.
*
* Also the ability to use normal taillights as brakelights
* by increasing their brightnes would be cool.
*
*/


class Brakelight{
  public:
    Brakelight(const uint8_t *pBrakelightArray, const uint8_t brakelightLedCount);
    void turnOn();
    void turnOff();

  private:
    const uint8_t *_pBrakelightArray;
    const uint8_t _brakelightLedCount;

};

#endif /* __BRAKELIGHT_H__ */
