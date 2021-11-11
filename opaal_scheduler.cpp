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
  this->events[1].begin(10,0,COL_SUNTOP);
  this->events[2].begin(19,0,COL_SUNSET);
  this->events[3].begin(20,0,COL_MOON);
  this->events[4].begin(22,0,COL_NIGHT);
}

/* -------------------------------------------------------------------- */
void OpaalScheduler::setTransitionTimeMillis(unsigned long newTransitionTimeMillis) {
  this->_transitionTime = newTransitionTimeMillis;
}

/* -------------------------------------------------------------------- */
void OpaalScheduler::simpleSetup(word newStartHour, word newStartMinute, word newDayDurationHours, word newMoonDurationHours, unsigned long newTransitionTimeMillis) {
  this->_lamp->changeColor(COL_NIGHT, 0);
  this->_transitionTime = newTransitionTimeMillis;
  this->events[0].setMinute((newStartHour*60)+newStartMinute);
  this->events[1].setMinute((newStartHour*60)+newStartMinute+30);
  this->events[2].setMinute((newStartHour*60)+newStartMinute+(newDayDurationHours*60)-30);
  this->events[3].setMinute((newStartHour*60)+newStartMinute+(newDayDurationHours*60));
  this->events[4].setMinute((newStartHour*60)+newStartMinute+(newDayDurationHours*60)+(newMoonDurationHours*60));
  for (byte ei=0; ei>4; ei++) { 
    this->events[ei].reset();
  }
}

/* -------------------------------------------------------------------- */
void OpaalScheduler::run() {
  for (byte ei=0; ei<EVENTS_NUMBER; ei++) {
    if(this->events[ei].isAvailable())  {
      this->_lamp->changeColor(this->events[ei].getAction(), this->_transitionTime);
    }
  }
}
