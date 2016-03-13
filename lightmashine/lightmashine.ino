// Version 1.5.1


#include "constants.h"
#include <avr/pgmspace.h>
#include "Lichtprogramme.h"

/*
** Nachfolgend: Hard core stuff. Nicht anfassen!
*/
#include "RecieverChannel.h"
#include "StateFromLeverUp.h"
#include "StateFromLeverDown.h"
#include "FlagState.h"
#include "Counter.h"
#include "StateFromButton.h"
#include "Led.h"
#include "PwmLed.h"
#include "SimPwmLed.h"
#include "NoopLed.h"
#include "ThrottleChannel.h"
#include "EepromAdapter.h"
#include "ThrottleCalibrator.h"
#include "Brakelight.h"
#include "Backfire.h"
#include "StandbyWatcher.h"


#define MAX_PROGRAMS 50
int modelStart = 0;
int programStarts[MAX_PROGRAMS];

Led* ledState[PIN_ANZAHL];

long frameStarted = 0;
int frame = -1;


//#define DEBUG_ON
#ifdef DEBUG_ON
#define DEBUG_INIT   Serial.begin(115200);
#define DEBUG(X)  Serial.println(X)
#else
#define DEBUG_INIT
#define DEBUG(X)
#endif

// Um einfach die Größe unabhängig vom Datentyp zu erhalten
#define ARRAY_LENGHT(X)  (sizeof(X)/sizeof(X[0]))

/************************************************************************************
*********************          Setup      *******************************************
************************************************************************************/

EepromAdapter eepromAdapter = EepromAdapter();
RecieverChannel reciever = RecieverChannel(SIG_PIN, RECIEVER_MIN, RECIEVER_MAX);
ThrottleChannel throttle = ThrottleChannel(THROTTLE_PIN,
                                                eepromAdapter.getMinThrottle(),
                                                eepromAdapter.getMaxThrottle(),
                                                eepromAdapter.getNeutralThrottle()
                                                );

Brakelight brakelight(led_pin_brakelights, (uint8_t)ARRAY_LENGHT(led_pin_brakelights));

Backfire backfire(led_pin_backfire, (uint8_t)ARRAY_LENGHT(led_pin_backfire), BACKFIRE_START);

StandbyWatcher standbyWatcher(STANDBY_WAIT_TIME);

int8_t throttleSignal = 0;

FlagState *powerState;
Counter *lightProgramSelect;

void setup() {
  DEBUG_INIT

  switchToSelectedModel();

  int programCount = setupProgramStarts();

  State *programSelectStateSource;
  State *powerStateSource;
  if (SWITCH_TYPE == 1) {
    programSelectStateSource = new StateFromLeverUp(&(reciever), ACTIVATE_PERIOD);
    powerStateSource = new StateFromLeverDown(&(reciever), ACTIVATE_PERIOD);
  }
  if (SWITCH_TYPE == 2) {
    programSelectStateSource = new StateFromButton(&(reciever), LESS_THAN, ACTIVATE_PERIOD);
    powerStateSource = new StateFromButton(&(reciever), GRATER_THAN, ACTIVATE_PERIOD);
  }
  lightProgramSelect = new Counter(programSelectStateSource, programCount);
  powerState = new FlagState(powerStateSource, START_WITH_LIGHT_ON);
  
  setupLedState();
  
  resetLedState();

  if(!eepromAdapter.holdsReasonableValues()){

    // somehow it's not working when passing ledState and then try to ledState[number]->set(myValue)
    ThrottleCalibrator calibrator = ThrottleCalibrator(&(throttle), &(eepromAdapter), led_pin_mapping, PIN_ANZAHL);
    calibrator.calibrate();
  }

  if (START_WITH_LIGHT_ON) {
    activateLightMashine();
  }


    DEBUG("Endpoints:\nmin Throttle: "+ String(throttle.getMinValue())+"\nmaxThrottle: "+String(throttle.getMaxValue())+"\nneutralThrottle: "+String(throttle.getNeutralValue()));
    DEBUG("Stored in Eeprom:\nmin Throttle: "+ String(eepromAdapter.getMinThrottle())+"\nmaxThrottle: "+String(eepromAdapter.getMaxThrottle())+"\nneutralThrottle: "+String(eepromAdapter.getNeutralThrottle()));

}




void switchToSelectedModel() {
  uint8_t model = 0;
  bool selected = false;
  while (!selected && modelSelectPins[model] != NICHT_DA) {
    if (digitalRead(modelSelectPins[model]) == HIGH) {
      selected = true;
    } else {
      model++;
    }
  }
  
  // for model 0 there is nothing to do
  if (model == 1) {
    for (int  i = 0; i < PIN_ANZAHL; i++) {
      led_pin_mapping[i] = led_pin_mapping_2[i];
    }
  }
  if (model == 2) {
    for (int  i = 0; i < PIN_ANZAHL; i++) {
      led_pin_mapping[i] = led_pin_mapping_3[i];
    }  }
  if (model == 3) {
    for (int  i = 0; i < PIN_ANZAHL; i++) {
      led_pin_mapping[i] = led_pin_mapping_4[i];
    }  }
  if (model == 4) {
    for (int  i = 0; i < PIN_ANZAHL; i++) {
      led_pin_mapping[i] = led_pin_mapping_5[i];
    }
  }
  DEBUG("model " + String(model) + " selected");
  
  // set modelStart
  int currentModel = 0;
  int ledLine = 0;
  while (currentModel < model) {
    while (!endOfProgramChain(readLeds(ledLine,0))) {
      ledLine++;
    }
    if (readLeds(ledLine,0) == MODEL_WECHSEL) {
      currentModel++;
      ledLine++;
      DEBUG("model " + String(currentModel) + " starts at line " + String(ledLine));
    }
  }
  modelStart = ledLine;
}





void setupLedState() {
  for (int i = 0; i < PIN_ANZAHL; i++) {
    int pinNr = led_pin_mapping[i];
    if (pinNr == NICHT_DA
#ifdef DEBUG_ON
        // pins 0 and 1 are used for serial communication. so let them be.
        || pinNr < 2
#endif    
    ) {
      ledState[i] = new NoopLed(pinNr);
    } else {
      ledState[i] = new SimPwmLed(pinNr);
    }
  }
}



int setupProgramStarts() {
  // very first program
  int programCounter = 0;
  programStarts[programCounter] = modelStart;
  programCounter++;
  
  int i = modelStart;
  // all others
  while (!endOfProgramChain(readLeds(i,0))) {
    if (readLeds(i,0) == PROGRAM_ENDE) {
      if (!endOfProgramChain(readLeds(i+1,0))) {
        programStarts[programCounter] = i+1;
        programCounter++;
      }
    }
    i++;
  }
  
  return programCounter;
}



bool endOfProgramChain(uint8_t ledValue) {
  return ledValue == FIN || ledValue == MODEL_WECHSEL;
}


















/************************************************************************************
*********************          Loop      *******************************************
************************************************************************************/



#define UPDATE_PERIOD 10
long counter = 0;
long lastTime = millis();
int iterationsToMatchUpdatePeriod = 1000;
int currentIterations = iterationsToMatchUpdatePeriod;
long lastUpdate = millis();
long globalNow = millis();
void loop() {



  if (throttle.hasNewValue()) {
    // So let's read the new value
    throttleSignal = throttle.getValue();

    standbyWatcher.update(throttleSignal);

    if (throttleSignal < 0) {
      // braking if throttle signal is negativ
      brakelight.turnOn();

    } else {
      // obvious we're not braking
      brakelight.turnOff();
      // TODO make sure that the LED will be turned off everytime!
      backfire.checkForActivation(throttleSignal);

      if (standbyWatcher.hasChanged())
      {
        if (!standbyWatcher.isStanby())
        {
          frame = standbyWatcher.getOldFrame();
        }
      }

    }
  }

  counter++;
  currentIterations--;
  reciever.read();
  if (currentIterations == 0) {
    globalNow = millis();
    currentIterations = iterationsToMatchUpdatePeriod;

    if ((globalNow - lastTime) > 1000) {
      lastTime = globalNow;

      if (standbyWatcher.hasChanged())
      {
        if (standbyWatcher.isStanby())
        {
          // TODO Change to Standby LED mode
          standbyWatcher.setOldFrame(frame);
          frame = 0;
          DEBUG("STANBY");
        }
      }

      DEBUG(String(counter) + " ips, " + String(iterationsToMatchUpdatePeriod) + " iterations per update, update period = " + String(globalNow - lastUpdate));
      DEBUG("Thottle signal in percent:"+String(throttle.getValue()));
      DEBUG("Thottle signal:"+String(throttle.getRawValue()));
      counter = 0;
    }

    long thisUpdateTook = globalNow - lastUpdate;
    if (thisUpdateTook > UPDATE_PERIOD) {
      iterationsToMatchUpdatePeriod-=100;
      if (iterationsToMatchUpdatePeriod <= 0) iterationsToMatchUpdatePeriod = 100;
    } else if (thisUpdateTook < UPDATE_PERIOD) {
      iterationsToMatchUpdatePeriod+=100;
    }
 
    lastUpdate = globalNow;

    powerState->read();
    lightProgramSelect->read();

    if (powerState->hasChanged()) {
      if (powerState->isOn()) {
        activateLightMashine();
      } else {
        deactivateLightMashine();
      }
    }

    if (lightProgramSelect->hasChanged()) {
      DEBUG("light program change " + String(lightProgramSelect->getCount()));
      frame = programStarts[lightProgramSelect->getCount()];
    }

    if (powerState->isOn()) {
      if (itIsTimeForNextFrame()) {
        nextFrame();
        copyFrameToLedState();
      }
    }
  }

   updateLeds();
}

void updateLeds() {
  for (int i = 0; i < PIN_ANZAHL; i++) {
    ledState[i]->update();
  }
}



void resetLedState() {
  // init ledState
  for (int i = 0; i < PIN_ANZAHL; i++) {
    ledState[i]->set(0);
  }
}



void activateLightMashine() {
  DEBUG("activate light mashine");
  lightProgramSelect->reset();
  frame = programStarts[lightProgramSelect->getCount()];
}



void deactivateLightMashine() {
  DEBUG("deactivate light mashine");
  resetLedState();
}



boolean itIsTimeForNextFrame() {
  long timeForNextFrame = frameStarted + FRAME_PAUSE;
  return globalNow >= timeForNextFrame;
}



void nextFrame() {
  frame++;
  if (readLeds(frame,0) == PROGRAM_ENDE) {
    frame = programStarts[lightProgramSelect->getCount()];
  }
  frameStarted = globalNow;
}



void copyFrameToLedState() {
  for (int i = 0; i < PIN_ANZAHL; i++) {
    ledState[i]->set(readLeds(frame,i));
  }
}



uint8_t readLeds(int lineNr, int rowNr) {
  return pgm_read_byte_near(&(leds[lineNr][rowNr]));
}
/*
uint8_t readStandbyLeds(int lineNr, int rowNr) {
  return pgm_read_byte_near(&(stanbyLeds[lineNr][rowNr]));
}

void setStandbyLeds()
*/
