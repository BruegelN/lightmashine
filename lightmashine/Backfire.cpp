#include "Backfire.h"
#include "rc_config.h" /* defines BACKFIRE_INTENSITY */

Backfire::Backfire(const uint8_t *pBackfireArray, const uint8_t backfireLedCount, const uint8_t startBackfire):
_pBackfireArray(pBackfireArray),
_backfireLedCount(backfireLedCount),
_startBackfire(startBackfire)
{
  for(uint8_t i = 0; i < _backfireLedCount; i++) {

    pinMode(_pBackfireArray[i],OUTPUT);

  }

}

void Backfire::checkForActivation(int8_t throttleValuePercentage){
  for(uint8_t i = 0; i < _backfireLedCount; i++)
  {
    digitalWrite(_pBackfireArray[i],LOW);
  }


  if(throttleValuePercentage >= _startBackfire)
  {
    static uint8_t randBackfireDelay;
    static uint8_t timeToBackfire;

    if( timeToBackfire == randBackfireDelay || timeToBackfire >= BACKFIRE_INTENSITY)
    {
      timeToBackfire = 0;
      randBackfireDelay = random(BACKFIRE_INTENSITY);
      for(uint8_t i = 0; i < _backfireLedCount; i++)
      {
        digitalWrite(_pBackfireArray[i],HIGH);
      }
    }
    timeToBackfire++;
  }
}
