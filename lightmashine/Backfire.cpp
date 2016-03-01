#include "Backfire.h"

Backfire::Backfire(const uint8_t *pBackfireArray, const uint8_t backfireLedCount, const uint8_t startBackfire):
_pBackfireArray(pBackfireArray),
_backfireLedCount(backfireLedCount),
_history {0},
_firstLed(0),
_startBackfire(startBackfire)
{
  for(uint8_t i = 0; i < _backfireLedCount; i++) {

    pinMode(_pBackfireArray[i],OUTPUT);

  }

}

void Backfire::checkForActivation(int8_t value){
  for(uint8_t i = 0; i < _backfireLedCount; i++)
  {
    digitalWrite(_pBackfireArray[i],LOW);
  }


  if(value >= _startBackfire)
  {
    static uint8_t randBackfireDelay;
    if( _firstLed == randBackfireDelay || _firstLed >= 30)
    {
      _firstLed = 0;
      randBackfireDelay = random(30);
      for(uint8_t i = 0; i < _backfireLedCount; i++)
      {
        digitalWrite(_pBackfireArray[i],HIGH);
      }
    }
    _firstLed++;
  }
}
