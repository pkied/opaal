/*
  opaal_channel.cpp - Class for control PWM on arduino output pin in OPAAL project.
  Created by Paweł Kiedrzyński, July 7, 2021.
  Released into the public domain.
*/

#include "opaal_channel.h"

void OpaalChannel::begin(byte newPinNumber) {
  this->reset(newPinNumber);
};

/* -------------------------------------------------------------------- */
void OpaalChannel::reset(byte newPinNumber) {
  this->_pinNumber = newPinNumber;
  this->_powerAdjust = 0.0;
  this->_powerLimit = 1.0;
  this->_realPower = 0.0;
  this->_realPowerChangeStep = 0.0;
  this->_realPowerChangeTarget = 0.0;
  analogWrite(this->_pinNumber, 0);
  pinMode(this->_pinNumber, OUTPUT);
  analogWrite(this->_pinNumber, 0);
  this->_stepTimer.begin(TICK);
};

/* -------------------------------------------------------------------- */
void OpaalChannel::changePower(float newRealPowerChangeTarget, unsigned long changeMillis) {
  if (newRealPowerChangeTarget > 1.0) newRealPowerChangeTarget = 1.0;
  if (newRealPowerChangeTarget < 0.0) newRealPowerChangeTarget = 0.0;
  this->_realPowerChangeTarget = newRealPowerChangeTarget;
  float stepCount = (float)changeMillis / (float)TICK;
  if (stepCount != 0) this->_realPowerChangeStep = (this->_realPowerChangeTarget - this->_realPower) / stepCount; //protection against division by zero
  else this->_realPowerChangeStep = (this->_realPowerChangeTarget - this->_realPower);
};

/* -------------------------------------------------------------------- */
void OpaalChannel::setPowerAdjust(float newPowerAdjust) {
  this->_powerAdjust = newPowerAdjust; 
}

/* -------------------------------------------------------------------- */
void OpaalChannel::setPowerLimit(float newPowerLimit) {
  this->_powerLimit = newPowerLimit; 
}

/* -------------------------------------------------------------------- */
void OpaalChannel::run() {
  if (this->_realPowerChangeStep != 0.0) {
    if (this->_stepTimer.available()) {
      this->_realPower = this->_realPower + this->_realPowerChangeStep;
      this->_stepTimer.restart();  
    }
    if ((this->_realPowerChangeStep >= 0 && this->_realPower >= this->_realPowerChangeTarget) || (this->_realPowerChangeStep < 0 && this->_realPower <= this->_realPowerChangeTarget)) {
      this->_realPower = this->_realPowerChangeTarget;
      this->_realPowerChangeStep = 0.0;
    }
  }
  float tempPower = (this->_realPower + (this->_realPower * this->_powerAdjust)) * this->_powerLimit;
  if (tempPower < 0.0) tempPower = 0.0;
  if (tempPower > 1.0) tempPower = 1.0;
  analogWrite(this->_pinNumber, (byte)round(255 * tempPower));
};
