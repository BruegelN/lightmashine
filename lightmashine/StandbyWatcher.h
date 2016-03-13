#ifndef __STANBY_WATCHER_H__
#define __STANBY_WATCHER_H__

#include "Arduino.h"

/*
* If you turn off your radio(with failsave) or put it away
* there won't be a siginificant change to your throttle value.
* After "standbyTimeOut"ms passed by without changes to throttle signal
* it's considered to be in standby mode.
* StandbyWatcher let's you change the current led frame if your in standby.
*/

class StandbyWatcher{

  public:

    /*
    * Constructor for standbywatcher
    *
    * param[in] uint64_t standbyTimeOut
    * The time after it's considered standby.
    */
    StandbyWatcher(uint64_t standbyTimeOut);

    // Set a new throttle value.
    void update(int8_t throttleValue);

    bool isStanby(void);
    bool hasChanged(void);

    // Set the current(thus old) frame before switch to standby.
    void setOldFrame(int frame);
    // Get the old frame which was used befor standby.
    int getOldFrame(void);

  private:
    uint64_t _lastTimeMoved;
    const uint64_t _standbyTimeOut;
    int _oldFrame;
    bool _standby;
    bool _hasChanged;

};

#endif // __STANBY_WATCHER_H__
