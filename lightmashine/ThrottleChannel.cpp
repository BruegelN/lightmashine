#include "ThrottleChannel.h"

#include <avr/interrupt.h>


// To prevent linker errors we need set it to '0'
ThrottleChannel* ThrottleChannel::ThrottleInterrupt::ownerChannel = NULL;

void ThrottleChannel::ThrottleInterrupt::record(ThrottleChannel *channel){
	ownerChannel = channel;
}

void ThrottleChannel::ThrottleInterrupt::serviceRoutine(){

	/*
	* TODO: first check if the right pin really changed,
	* because there might be more than one interrupt pin on a specific PORT
	*/

	if(ownerChannel != NULL){
		if(digitalRead(ownerChannel->_pin)){
			// if the pin is HIGH it means the signal just rised so we start to record time
    		ownerChannel->_timeRising = micros();
  		}else{
  			// else it just finished so we can calculate the signal time by substract the actual time with the start time
    		ownerChannel->_tmpValue = (uint16_t)(micros() - ownerChannel->_timeRising);
    	} 

	}

}

ThrottleChannel::ThrottleChannel(uint8_t pin):
_pin(pin)
{
	ThrottleInterrupt::record(this);

	_value = NULL;
	_tmpValue = NULL;
	_timeRising = NULL;

	pinMode(_pin, INPUT_PULLUP);

	// some handy Arduino macros seen at: http://playground.arduino.cc/Main/PinChangeInterrupt
  // enable pin
  *digitalPinToPCMSK(_pin) |= bit (digitalPinToPCMSKbit(_pin));
  // clear any outstanding interrupt
  PCIFR  |= bit (digitalPinToPCICRbit(_pin));
  // enable interrupt for the group
  PCICR  |= bit (digitalPinToPCICRbit(_pin));

	// enanble gobal interupts
	sei();
}

const uint8_t ThrottleChannel::getAttachedPin() {

	return _pin;

}

uint16_t ThrottleChannel::getValue() {

	// turn off interupts
	cli();
	// copy the value
	_value = _tmpValue;
	// turn interupts back on
	sei();

	return _value;

}
