#include "Backfire.h"

Backfire::Backfire(uint8_t pin):
_pin(pin),
_history {0}
{
  pinMode(_pin, OUTPUT);

}

void Backfire::checkForActivation(int8_t value){

  digitalWrite(_pin,LOW);
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

      digitalWrite(_pin, HIGH);

    }
  }
}
