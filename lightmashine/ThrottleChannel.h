#ifndef __THROTTLE_H__
#define __THROTTLE_H__

#include "Arduino.h"


/*
*
* For more informaition (only german):
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
    ThrottleChannel();
    ThrottleChannel(uint8_t pin);
    const uint8_t getAttachedPin();
    uint16_t getValue();

  private:
    /* prevent compiler optimization, because it will be modyfied in ISR so it need's to be "accessible from somewhere else" */
    volatile uint32_t _timeRising;
    volatile uint32_t _tmpValue;
    uint16_t _value;
    const uint8_t _pin;

};
#endif  /* __THROTTLE_H__ */
