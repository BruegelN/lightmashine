#include "ThrottleCalibrator.h"

ThrottleCalibrator::ThrottleCalibrator(ThrottleChannel* throttle, EepromAdapter* eepromAdapter, uint8_t* ledPins, uint8_t ledNumber){

  _throttle = throttle;
  _eepromAdapter = eepromAdapter;
  _ledPins = ledPins;
  _ledNumber = ledNumber;

}

void ThrottleCalibrator::calibrate(){

   delay(1000);
   _eepromAdapter->saveNeutralThrottle(_throttle->getValue());
   _throttle->setNeutralValue();
   
   ledBlinkToCheck();

   delay(3000);
   _eepromAdapter->saveMaxThrottle(_throttle->getValue());
   _throttle->setMaxValue();

   ledBlinkToCheck();
   ledBlinkToCheck();

   delay(3000);
   _eepromAdapter->saveMinThrottle(_throttle->getValue());
   _throttle->setMinValue();

   ledBlinkToCheck();
   ledBlinkToCheck();
   ledBlinkToCheck();

   delay(500);

   _throttle->updateReverseMode();

}

void ThrottleCalibrator::ledBlinkToCheck(){

  for (int i = 0; i < _ledNumber; i++) {
    digitalWrite(_ledPins[i], HIGH);
  }

  delay(100);

  for (int i = 0; i < _ledNumber; i++) {
    digitalWrite(_ledPins[i], LOW);
  }
  delay(100);


}
