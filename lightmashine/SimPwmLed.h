#ifndef __SIM_PWN_LED__
#define __SIM_PWN_LED__

#include "Arduino.h"
#include "Led.h"
#include "constants.h"

#define NOT_SET 255

class SimPwmLed: public Led {
  public:
    SimPwmLed(uint8_t pin);
    void set(uint8_t percent);
    void update();
  private:
    void fastWrite(uint8_t newState);
    
    uint8_t _pin;
    int _updatesBetweenFrames;
    int _updatesPerTargetLightnessPoint;
    int _updatesUntilNextTargetLightPoint;
    bool _increasing;

    uint8_t _fromTargetLightness;
    uint8_t _toTargetLightness;

    int _targetLightness;
    uint8_t _counter;
    uint8_t _state;
};

#endif
