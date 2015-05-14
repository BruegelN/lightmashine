#ifndef __THROTTLE_H__
#define __THROTTLE_H__

#include "Arduino.h"


class ThrottleChannel {

  class ThrottleInterrupt {

    public:
      static void record(ThrottleChannel *channel);

    private:
		  static ThrottleChannel* ownerChannel;
      /*
      PCINT1_vect is just the interrupt vector for analoge pins 
      TODO map pins to interrupt verctors !
      */
		  static void serviceRoutine() __asm__("PCINT1_vect") __attribute__((__signal__, __used__, __externally_visible__));

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
    volatile uint32_t _tmpValue;
    volatile uint16_t _value;
    const uint8_t _pin;

};
#endif  /* __THROTTLE_H__ */
