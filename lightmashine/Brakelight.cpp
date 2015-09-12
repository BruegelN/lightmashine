#include "Brakelight.h"

Brakelight::Brakelight(const uint8_t *pBrakelightArray, const uint8_t brakelightLedCount):
_pBrakelightArray(pBrakelightArray),
_brakelightLedCount(brakelightLedCount)
{

  for(uint8_t i = 0; i < _brakelightLedCount; i++) {

    pinMode(_pBrakelightArray[i],OUTPUT);

  }

}

void Brakelight::turnOn() {

  for(uint8_t i = 0; i < _brakelightLedCount; i++) {

    digitalWrite(_pBrakelightArray[i],HIGH);

  }

}

void Brakelight::turnOff() {

  for(uint8_t i = 0; i < _brakelightLedCount; i++) {

    digitalWrite(_pBrakelightArray[i],LOW);

  }

}
