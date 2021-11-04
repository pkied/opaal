/*
  opaal_fan.h - Class for control fans in OPAAL project.
  Created by Paweł Kiedrzyński, October 23, 2021.
  Released into the public domain.
*/

#include "opaal_fan.h"

/* -------------------------------------------------------------------- */
void OpaalFan::run() {
  byte temp = round(RTC.temperature() / 4.0);
  if ((temp >= this->_startTemp) && !this->_on) {
    this->_fanChannel.changePower(1.0,0);
    this->_on = true;
  }
  if ((temp <= this->_stopTemp) && this->_on) {
    this->_fanChannel.changePower(0.0,0);
    this->_on = false;
  }
  this->_fanChannel.run();
}

/* -------------------------------------------------------------------- */
void OpaalFan::begin(byte newStartTemp, byte newStopTemp, byte newPinNumber) {
  this->_startTemp = newStartTemp;
  this->_stopTemp = newStopTemp;
  this->_pinNumber = newPinNumber;
  this->_fanChannel.begin(this->_pinNumber);
  this->_on = false;
}

/* -------------------------------------------------------------------- */
bool OpaalFan::isOn() {
  return this->_on;
}
