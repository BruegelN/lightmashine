#include "StandbyWatcher.h"


StandbyWatcher::StandbyWatcher(uint64_t standbyTimeOut):
_lastTimeMoved(0),
_standbyTimeOut(standbyTimeOut),
_oldFrame(0),
_standby(false),
_hasChanged(false)
{
}


void StandbyWatcher::update(int8_t throttleValue)
{
  if(throttleValue != 0)
  {
    // if the throttle value is not equal to zero we're obviously not moving
    _lastTimeMoved = millis();
  }

  if((millis()-_lastTimeMoved) >= _standbyTimeOut)
  {
    // enter standby-mode
    if(!_standby)
    {
      // if haven't been in standy-mode before
      // set _hasChanged to true to check it in hasChanged().
      _standby = true;
      _hasChanged = true;
    }
    else
    {
      // are already in standby-mode, thus state has not changed!
      _hasChanged = false;
    }

  }
  else
  {
    // we're not in standby-mode
    if(_standby)
    {
      // previously been in standby-mode
      // so set the _hasChanged and reset/disable _standby
      _standby = false;
      _hasChanged = true;
    }
    else
    {
      // haven't been in standby-mode before, thus state has not changed!
      _hasChanged = false;
    }
  }
}


bool StandbyWatcher::isStandby(void)
{
  return _standby;
}


bool StandbyWatcher::hasChanged(void)
{
  if(_hasChanged)
  {
    _hasChanged = false;
    return true;
  }
  else
  {
    return _hasChanged;
  }
}


void StandbyWatcher::setOldFrame(int frame)
{
  _oldFrame = frame;
}


int StandbyWatcher::getOldFrame()
{
  return _oldFrame;
}
