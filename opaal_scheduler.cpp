/*
  opaal_scheduler.h - Class for schduling lamp color changes in OPAAL project.
  Created by Paweł Kiedrzyński, October 08, 2021.
  Released into the public domain.
*/

#include "opaal_scheduler.h"

/* -------------------------------------------------------------------- */
void OpaalScheduler::begin(OpaalLamp* newLamp) {
  this->_lamp = newLamp;
  this->_lamp->changeColor(COL_NIGHT, 0);
  this->events[0].begin(8,0,COL_SUNRISE);
  this->events[1].begin(8,5,COL_SUNTOP);
  this->events[2].begin(8,10,COL_SUNSET);
  this->events[3].begin(8,15,COL_MOON);
  this->events[4].begin(9,0,COL_NIGHT);
}

/* -------------------------------------------------------------------- */
void OpaalScheduler::simpleSetup(word newStartHour, word newStartMinute, word newDayDurationHours, word newMoonDurationHours, unsigned long newTransitionTimeMillis) {
  this->_transitionTime = newTransitionTimeMillis;
  this->events[0].begin(newStartHour+newStartMinute,0,COL_SUNRISE);
  this->events[1].begin(newStartHour+newStartMinute,30,COL_SUNTOP);
  this->events[2].begin(newStartHour+newStartMinute+newDayDurationHours-1,30,COL_SUNSET);
  this->events[3].begin(newStartHour+newStartMinute+newDayDurationHours,0,COL_MOON);
  this->events[4].begin(newStartHour+newStartMinute+newDayDurationHours+newMoonDurationHours-1,30,COL_NIGHT);
}

/* -------------------------------------------------------------------- */
void OpaalScheduler::run() {
  for (byte ei=0; ei<EVENTS_NUMBER; ei++) {
    if(this->events[ei].isAvailable())  {
      this->_lamp->changeColor(this->events[ei].getAction(), this->_transitionTime);
    }
  }
}
