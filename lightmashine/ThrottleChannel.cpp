#include "ThrottleChannel.h"

#include <avr/interrupt.h>


// To prevent linker errors we need set it to '0'
ThrottleChannel* ThrottleChannel::ThrottleInterrupt::ownerChannel = NULL;

void ThrottleChannel::ThrottleInterrupt::record(ThrottleChannel *channel){
	ownerChannel = channel;
}

void ThrottleChannel::ThrottleInterrupt::serviceRoutine(){

	if(ownerChannel != NULL){
		if(digitalRead(ownerChannel->_pin)){
			// if the pin is HIGH it means the signal just rised so we start to record time
    		ownerChannel->_tmpValue = micros();
  		}else{
  			// else it just finished so we can calculate the signal time by substract the actual time with the start time
    		ownerChannel->_value = (uint16_t)(micros() - ownerChannel->_tmpValue);
    	} 

	}

}

ThrottleChannel::ThrottleChannel(uint8_t pin):
_pin(pin)
{

	pinMode(_pin, INPUT_PULLUP);
	_value = NULL;

	ThrottleInterrupt::record(this);
	// enanble gobal interupts
	sei();
}

const uint8_t ThrottleChannel::getAttachedPin() {

	return _pin;

}

uint16_t ThrottleChannel::getValue() {
	
	return _value;

}
