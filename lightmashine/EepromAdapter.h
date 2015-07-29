#ifndef __EEPROMADAPTER_H__
#define __EEPROMADAPTER_H__

#include <avr/eeprom.h>
#include "stdint.h"

/*
* This class allows to store/load all relevant information for lightmashine in eeprom.
* Eeprom will keep the values after powering off the controller, which makes it ideal for this job.
* 
* Extensions should be implementet by the time they're needed.
*
*/


class EepromAdapter {
  public:
    EepromAdapter();

    uint16_t getMinThrottle();
    uint16_t getMaxThrottle();
    uint16_t getNeutralThrottle();

    void saveMinThrottle(uint16_t minThrottle);
    void saveMaxThrottle(uint16_t maxThrottle);
    void saveNeutralThrottle(uint16_t neutralThrottle);

    // This function may take a little bit because writing to Eeprom is quite slow !
    void saveEndpoints();

    // to check if we have correct values stored in Eeprom if not calibrate it
    bool holdsReasonableValues();

  private:

    // These are the eeprom addreses to store neutral point and endpoints.
    uint16_t *_addressMinThrottle = new unsigned int (0);
    uint16_t *_addressMaxThrottle = new unsigned int (2);
    uint16_t *_addressNeutralThrottle = new unsigned int (4);

    uint16_t _minThrottle;
    uint16_t _maxThrottle;
    uint16_t _neutralThrottle;

    void loadEndpoints();

    bool valuesAreSorted();
    bool valuesAreInRange();

};

#endif /* __EEPROMADAPTER_H__ */
