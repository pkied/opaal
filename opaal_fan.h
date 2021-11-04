/*
  opaal_fan.h - Class for control fans in OPAAL project.
  Created by Paweł Kiedrzyński, October 23, 2021.
  Released into the public domain.
*/

#ifndef opaal_fan_h
#define opaal_fan_h

#include <Arduino.h>
#include <DS3232RTC.h>
#include "opaal_channel.h"

class OpaalFan {
  private:
    OpaalChannel _fanChannel;
    bool _on;
    byte _startTemp;
    byte _stopTemp;
    byte _pinNumber;
  public:
    void begin(byte newStartTemp, byte newStopTemp, byte newPinNumber);
    void run();
    bool isOn();
};
#endif
