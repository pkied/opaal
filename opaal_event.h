/*
  opaal_event.h - Class for handling scheduler events in OPAAL project.
  Created by Paweł Kiedrzyński, October 08, 2021.
  Released into the public domain.
*/

#ifndef opaal_event_h
#define opaal_event_h

#include <Arduino.h>
#include <DS3232RTC.h>

class OpaalEvent {
  private:
    word _minute;
    byte _action;
    bool _isAvailable;
  public:
    void setHourMinute(word newHour, word newMinute);
    void setAction(byte newAction);
    byte getAction();
    bool isAvailable();
    void reset();
    void begin(word newHour, word newMinute, byte newAction);
};
#endif
