#ifndef __THROTTLE_H__
#define __THROTTLE_H__

#include "Arduino.h"


// neutral + - this value is still considered neutral e.g. in isBraking-method
#define THROTTLE_NEUTRAL_RANGE 15

/*
* The ThrottleChannel class allows to get all necessary information
* about the real signal from the radio's throttle channel.
* We don't need to care about exacte singal values, because ThrottleChannel will do this for us.
*
* The ThrottleInterrupt class is used to catch the real interrupt cycles.
* The ThrottleInterrupt::serviceRoutine is basicly the InterruptServiceRoutine where the interrupts are measured.
* Therefor we don't need to use the C-Style ISR() macro in the main programm.
* For more informaition on how to deal with interrupts (on AVR's) in an C++ way (but sadly german):
* http://www.mikrocontroller.net/articles/AVR_Interrupt_Routinen_mit_C%2B%2B
*
*/

class ThrottleChannel {

  class ThrottleInterrupt {

    public:
      static void record(ThrottleChannel *channel);

    private:
		  static ThrottleChannel* ownerChannel;
      /*
      __vector_4 is just the interrupt vector for analoge pins on Atmega 328p
      If you try attach the interrupt to other pins you might have an unhandled interrupt which causes a reset.
      TODO map pins to interrupt verctors !
      */
		  static void serviceRoutine() __asm__("__vector_4") __attribute__((__signal__, __used__, __externally_visible__));

	};

  // to get acces to the ISR
  friend ThrottleInterrupt;

  public:

    ThrottleChannel(uint8_t pin,
                    uint16_t minValue,
                    uint16_t maxValue,
                    uint16_t neutralValue
                    );

     uint8_t getAttachedPin();

    /*
    * This will only return the measured time in microseconds.
    * But most of the time the true possition is needed.
    */
    uint16_t getRawValue();
    bool hasNewValue();

    /*
    * This will return the true possition :
    * +100% => full throttle
    *    0% => netral
    * -100% => full brake/ backwards
    *
    * For calculating these values min-, max- and neutralValue
    * are needed and information whether if the ThrottleChannel is in reverseMode.
    */
    int8_t getValue();


    uint16_t getMinValue();
    uint16_t getMaxValue();
    uint16_t getNeutralValue();

    /*
    * ATTENTION: Allways retruns true if between neutral and full reverse!
    * So if you're driving backwards it will return true, too.
    * TODO distinguish between really braking and driving backwards.
    * e.g. on most ESC's you have to "brake" twice to drive backwards
    * (brake => return to neutral => reverse)
    */
    bool isBraking();

  private:
    // prevent compiler optimization, because it will be modyfied in ISR so it need's to be "accessible from somewhere else"
    volatile uint32_t _timeRising;
    volatile uint32_t _tmpValue;

    uint16_t _value;

    const uint8_t _pin;
    bool _hasNewValue;

    /*
    * Regularly the neutralValue is around 1500.
    * A minValue between 900 and neutralValue
    * and maxValue between neutralValue and 2100
    * is considered to be normal mode.
    * If it is the other way around we call this mode reverse.
    */
    bool _reverseMode;

    uint16_t _minValue;
    uint16_t _maxValue;
    uint16_t _neutralValue;

    // copy newest signal to variable which is not shared with ISR
    void copyValue();

    // to acces the following functions when calibrating
    friend class ThrottleCalibrator;
    void setMinValue();
    void setMaxValue();
    void setNeutralValue();

    void updateReverseMode();

};
#endif  /* __THROTTLE_H__ */
