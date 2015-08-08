#include "Brakelight.h"

Brakelight::Brakelight(uint8_t brakelightPin):
_brakelightPin(brakelightPin) {

  pinMode(_brakelightPin, OUTPUT);

}

void Brakelight::turnOn() {

  digitalWrite(_brakelightPin, HIGH);

}

void Brakelight::turnOff() {

  digitalWrite(_brakelightPin, LOW);

}
