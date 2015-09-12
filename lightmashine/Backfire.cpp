#include "Backfire.h"

Backfire::Backfire(const uint8_t *pBackfireArray, const uint8_t backfireLedCount):
_pBackfireArray(pBackfireArray),
_backfireLedCount(backfireLedCount),
_history {0}
{
  for(uint8_t i = 0; i < _backfireLedCount; i++) {

    pinMode(_pBackfireArray[i],OUTPUT);

  }

}

void Backfire::checkForActivation(int8_t value){

  for(uint8_t i = 0; i < _backfireLedCount; i++) {

    digitalWrite(_pBackfireArray[i],LOW);

  }


  _history[9] = _history[8];
  _history[8] = _history[7];
  _history[7] = _history[6];
  _history[6] = _history[5];
  _history[5] = _history[4];
  _history[4] = _history[3];
  _history[3] = _history[2];
  _history[2] = _history[1];
  _history[1] = _history[0];
  _history[0] = value;

  if((_history[0] >= 40) && (_history[9] >= 0)){

    if(_history[9] - _history[0] >= 40){

      for(uint8_t i = 0; i < _backfireLedCount; i++) {

        digitalWrite(_pBackfireArray[i],HIGH);

      }

    }
  }
}
