/*
  opaal_channel.h - Class for control PWM on arduino output pin in OPAAL project.
  Created by Paweł Kiedrzyński, July 7, 2021.
  Released into the public domain.

  Used libraries:
  Timers.h, Copyright (c) 2016 Łukasz Tretyn, MIT License, https://github.com/nettigo/Timers
*/

#ifndef opaal_channel_h
#define opaal_channel_h

#include <Arduino.h>
#include <Timers.h>

#define TICK 100

class OpaalChannel {
  private:
    byte _pinNumber;
    float _powerAdjust;
    float _powerLimit;
    float _realPower;
    float _realPowerChangeStep;
    float _realPowerChangeTarget;
    Timer _stepTimer;
  public:
    void begin(byte newPinNumber);
    void reset(byte newPinNumber);
    void setPowerAdjust(float newPowerAdjust);
    void setPowerLimit(float newPowerLimit);
    void changePower(float newRealPowerChangeTarget, unsigned long changeMillis);
    void run();
};
#endif
