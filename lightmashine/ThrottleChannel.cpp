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

			ownerChannel->_hasNewValue = true;

	}

}

ThrottleChannel::ThrottleChannel(uint8_t pin,
																uint16_t minValue,
																uint16_t maxValue,
																uint16_t neutralValue
																):
_pin(pin)
{
	ThrottleInterrupt::record(this);

	_value = NULL;
	_tmpValue = NULL;
	_timeRising = NULL;
	_hasNewValue = false;
	_minValue = minValue;
	_maxValue = maxValue;
	_neutralValue = neutralValue;

	updateReverseMode();

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

uint16_t ThrottleChannel::getRawValue() {

	// because we will get the newest value by calling this funktion
	_hasNewValue = false;

	copyValue();

	return _value;

}

bool ThrottleChannel::hasNewValue(){

	return _hasNewValue;

}
uint16_t ThrottleChannel::getMinValue(){

	return _minValue;

}
uint16_t ThrottleChannel::getMaxValue(){

	return _maxValue;

}
uint16_t ThrottleChannel::getNeutralValue(){

	return _neutralValue;

}

bool ThrottleChannel::isBraking(){

	/*
	* Regularly the neutralValue is around 1500.
	* A minValue between 900 and neutralValue
	* and maxValue between neutralValue and 2100
	* is considered to be normal mode.
	* If it is the other way around we call this mode reverse.
	*/
	copyValue();

	if(!_reverseMode && _value<(_neutralValue - THROTTLE_NEUTRAL_RANGE)){
		return true;
	}else if (_reverseMode && _value>(_neutralValue + THROTTLE_NEUTRAL_RANGE)){
		return true;
	}else{
		return false;
	}

}

int8_t ThrottleChannel::getValue(){

	getRawValue();

	/*
	* Regularly the neutralValue is around 1500.
	* A minValue between 900 and neutralValue
	* and maxValue between neutralValue and 2100
	* is considered to be normal mode.
	* If it is the other way around we call this mode reverse.
	*/

	if (_value < (_neutralValue + THROTTLE_NEUTRAL_RANGE) && _value > (_neutralValue - THROTTLE_NEUTRAL_RANGE)){

		// If it's in neutrale range we can ignore the reverse mode
		return 0;

	}else if (_reverseMode){

		if ((_neutralValue + THROTTLE_NEUTRAL_RANGE) <= _value){

			// Backwards therefor negativ
			return map(_value, (_neutralValue + THROTTLE_NEUTRAL_RANGE), _minValue, 0, -100);

		} else {

			// Forward therefor positiv
			return map(_value, (_neutralValue - THROTTLE_NEUTRAL_RANGE), _maxValue, 0, 100);

		}

	} else {
		// Normal mode

		if ((_neutralValue + THROTTLE_NEUTRAL_RANGE) <= _value){

			// Forward therefor positiv
			return map(_value, (_neutralValue + THROTTLE_NEUTRAL_RANGE), _maxValue, 0, 100);

		} else {

			// Backwards therefor negativ
			return map(_value, (_neutralValue - THROTTLE_NEUTRAL_RANGE), _minValue, 0, -100);

		}

	}

}

void ThrottleChannel::copyValue(){

	// turn off interupts
	cli();
	// copy the value
	_value = _tmpValue;
	// turn interupts back on
	sei();

}
void ThrottleChannel::setMinValue(){

	copyValue();
	_minValue = _value;

}
void ThrottleChannel::setMaxValue(){

	copyValue();
	_maxValue = _value;

}
void ThrottleChannel::setNeutralValue(){

	copyValue();
	_neutralValue = _value;

}
void ThrottleChannel::updateReverseMode(){

	if(_minValue > _maxValue){
		_reverseMode = true;
	}else{
		_reverseMode =false;
	}

}
