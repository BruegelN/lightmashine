#ifndef __BRAKELIGHT_H__
#define __BRAKELIGHT_H__

#include "Arduino.h"

/*
* This is basically class around an led which is used as brakelight.
* By now there is only one pin availible to connect to an led.
* So if you want to use more than one led as brakelight
* an external transitor is recommended.
*
* Maybe it might be cool to support more than one brakelight led later.
* Also the ability to use normal taillights as brakelights
* by increasing their brightnes would be cool.
*
*/


class Brakelight{
  public:
    Brakelight(uint8_t brakelightPin);
    void turnOn();
    void turnOff();

  private:
    const uint8_t _brakelightPin;

};

#endif /* __BRAKELIGHT_H__ */
