#ifndef __THROTTLECALIBRATOR_H__
#define __THROTTLECALIBRATOR_H__

#include "Arduino.h"
#include "EepromAdapter.h"
#include "ThrottleChannel.h"
#include "Led.h"
#include "constants.h"

class ThrottleCalibrator{

  public:
    ThrottleCalibrator(ThrottleChannel* throttle, EepromAdapter* eeprom, uint8_t* ledPins, uint8_t ledNumber);
    /*
    * When calibrating first the neutral value is set afterwards all leds will blink ONCE.
    * Then full throttle is set afterwards all leds will blink TWICE.
    * At the end full brake is set and afterwards all leds will blink THREE TIMES.
    *
    * Shortly afterwards lightmashine will start working normaly.
    * This calibration need to be done on the first use of lightmashine
    * or if you change throttle EPA or DualRate setting on your radio.
    * All values will be updated in ThrottleChannel object and saved to Eeprom.
    */
    void calibrate();
  private:
    ThrottleChannel* _throttle;
    EepromAdapter* _eepromAdapter;
    uint8_t* _ledPins;
    uint8_t _ledNumber;
    void ledBlinkToCheck();


};

#endif  /* __THROTTLECALIBRATOR_H__ */
