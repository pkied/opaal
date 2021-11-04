/*
  opaal_lamp.cpp - Class for control led lamp in OPAAL project.
  Created by Paweł Kiedrzyński, September 28, 2021.
  Released into the public domain.
*/

#include "opaal_lamp.h"

/* -------------------------------------------------------------------- */
void OpaalLamp::setOn(bool newOn) {
  this->_on = newOn;
}

/* -------------------------------------------------------------------- */
void OpaalLamp::setTemperature(float newTemperature) {
  this->_temperature = newTemperature;
}

/* -------------------------------------------------------------------- */
void OpaalLamp::setPower(float newPower) {
  this->_power = newPower;
}

/* -------------------------------------------------------------------- */
void OpaalLamp::changeColor(byte newColor, unsigned long changeMillis) {
  this->_color = newColor;
  for (byte chi=0; chi<CHI_COUNT; chi++) {
    this->_channel[chi].changePower(c_lampColorProfiles[this->_color][chi], changeMillis);  
  }
}
/* -------------------------------------------------------------------- */
byte OpaalLamp::getColor() {
  return this->_color;
}

/* -------------------------------------------------------------------- */
void OpaalLamp::run() {
  for (byte chi=0; chi<CHI_COUNT; chi++) {
    this->_channel[chi].setPowerAdjust(c_lampTemperatureProfiles[chi] * this->_temperature);  
    this->_channel[chi].setPowerLimit(this->_power);  
    this->_channel[chi].run();  
  }
}

/* -------------------------------------------------------------------- */
void OpaalLamp::begin() {
  for (byte chi=0; chi<CHI_COUNT; chi++) {
    this->_channel[chi].begin(c_lampChannelPins[chi]);
  }
}
