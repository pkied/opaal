/*
  opaal_config.h - Class for keep and handling configuration in OPAAL project.
  Created by Paweł Kiedrzyński, October 08, 2021.
  Released into the public domain.
*/

#ifndef opaal_config_h
#define opaal_config_h

#include <Arduino.h>
#include <avr/eeprom.h>

class OpaalConfig {
  private:
    word _cnfStartHour = 8;
    word _cnfStartMinute = 0;
    word _cnfDayDurationHours = 12;
    word _cnfMoonDurationHours = 4;
    float _cnfLampPower = 0.7;
    float _cnfLightTemperature = 0.0;
    bool _isSaving = 0;
  public:
    void begin();
    void save();
    void load();
    word getCnfStartHour();
    word getCnfStartMinute();
    word getCnfDayDurationHours();
    word getCnfMoonDurationHours();
    float getCnfLampPower();
    float getCnfLightTemperature();
    void setCnfStartHour(word newStartHour);
    void setCnfStartMinute(word newStartMinute);
    void setCnfDayDurationHours(word newDayDurationHours);
    void setCnfMoonDurationHours(word newMoonDurationHours);
    void setCnfLampPower(float newLampPower);
    void setCnfLightTemperature(float newLightTemperature);
};
#endif
