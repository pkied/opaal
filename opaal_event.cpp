/*
  opaal_event.cpp - Class for handling lamp scheduler events in OPAAL project.
  Created by Paweł Kiedrzyński, November 17, 2021.
  Released into the public domain.
*/

#include "opaal_event.h"

/* -------------------------------------------------------------------- */
void OpaalEvent::setHourMinute(word newHour, word newMinute) {
  this->_minute = (newHour * 60) + newMinute; 
}

/* -------------------------------------------------------------------- */
void OpaalEvent::setAction(byte newAction) {
  this->_action = newAction;
}

/* -------------------------------------------------------------------- */
byte OpaalEvent::getAction() {
  return this->_action;
}

/* -------------------------------------------------------------------- */
bool OpaalEvent::isAvailable() {
  word currentMinute = minute() + (hour() * 60);
  if (currentMinute < this->_minute) this->_isAvailable = false;
  if ((currentMinute >= this->_minute) && !this->_isAvailable) {
    this->_isAvailable = true;
    return true;
  }
  return false;
}

/* -------------------------------------------------------------------- */
void OpaalEvent::reset() {
  this->_isAvailable = false;
}

/* -------------------------------------------------------------------- */
void OpaalEvent::begin(word newHour, word newMinute, byte newAction) {
  setHourMinute(newHour, newMinute);
  setAction(newAction);
}
