/*
  opaal_scheduler.h - Class for schduling lamp color changes in OPAAL project.
  Created by Paweł Kiedrzyński, October 08, 2021.
  Released into the public domain.
*/

#ifndef opaal_scheduler_h
#define opaal_scheduler_h

#include <Arduino.h>
#include "opaal_event.h"
#include "opaal_lamp.h"

#define EVENTS_NUMBER 5

class OpaalScheduler {
  private:
    OpaalLamp* _lamp;
    OpaalEvent events[EVENTS_NUMBER];
    unsigned long _transitionTime = 10000;//3600000;
  public:
    void begin(OpaalLamp* newLamp);
    void simpleSetup(word newStartHour, word newStartMinute, word newDayDurationHours, word newMoonDurationHours, unsigned long newTransitionTimeMillis);
    void run();
};
#endif
