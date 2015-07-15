#include "EepromAdapter.h"

EepromAdapter::EepromAdapter(){

  loadEndpoints();

}


uint16_t EepromAdapter::getMinThrottle(){

  return _minThrottle;

}

uint16_t EepromAdapter::getMaxThrottle(){

  return _maxThrottle;
}

uint16_t EepromAdapter::getNeutralThrottle(){

  return _neutralThrottle;

}

void EepromAdapter::saveMinThrottle(uint16_t minThrottle){

  _minThrottle = minThrottle;
  eeprom_write_word(_addressMinThrottle, _minThrottle);
  eeprom_busy_wait();

}
void EepromAdapter::saveMaxThrottle(uint16_t maxThrottle){

  _maxThrottle = maxThrottle;
  eeprom_write_word(_addressMaxThrottle, _maxThrottle);
  eeprom_busy_wait();

}
void EepromAdapter::saveNeutralThrottle(uint16_t neutralThrottle){

  _neutralThrottle = neutralThrottle;
  eeprom_write_word(_addressNeutralThrottle, _neutralThrottle);
  eeprom_busy_wait();

}

void EepromAdapter::loadEndpoints(){

  _minThrottle = eeprom_read_word(_addressMinThrottle);
  eeprom_busy_wait();
  _maxThrottle = eeprom_read_word(_addressMaxThrottle);
  eeprom_busy_wait();
  _neutralThrottle = eeprom_read_word(_addressNeutralThrottle);
  eeprom_busy_wait();

}

void EepromAdapter::saveEndpoints(){

  eeprom_write_word(_addressMinThrottle,_minThrottle);
  eeprom_busy_wait();
  eeprom_write_word(_addressMaxThrottle, _maxThrottle);
  eeprom_busy_wait();
  eeprom_write_word(_addressNeutralThrottle, _neutralThrottle);
  eeprom_busy_wait();

}

bool EepromAdapter::holdsReasonableValues(){

  if(valuesAreSorted() && valuesAreInRange()){

    return true;

  }else{

    return false;

  }
}


bool EepromAdapter::valuesAreSorted(){

  if((_minThrottle < _neutralThrottle) && (_neutralThrottle < _maxThrottle)){
    // Throttle is in "NORMAL" direction
    return true;

  }else if((_minThrottle > _neutralThrottle) && (_neutralThrottle > _maxThrottle)){
    // Throttle is in "REVERSE"
    return true;

  }else{

    return false;

  }

}

bool EepromAdapter::valuesAreInRange(){

  if((_minThrottle > 900) && (_maxThrottle < 2100)){

    return true;

  }else if ((_minThrottle < 2100) && (_maxThrottle > 900)){

    return true;

  }else{

    return false;

  }
}
