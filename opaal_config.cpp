/*
  opaal_config.cpp - Class for keep and handling configuration in OPAAL project.
  Created by Paweł Kiedrzyński, October 08, 2021.
  Released into the public domain.
*/

#include "opaal_config.h"

/* -------------------------------------------------------------------- */
void OpaalConfig::begin() {
}

/* -------------------------------------------------------------------- */
word OpaalConfig::getCnfStartHour() {
  return this->_cnfStartHour;
}

/* -------------------------------------------------------------------- */
word OpaalConfig::getCnfStartMinute() {
  return this->_cnfStartMinute;
}

/* -------------------------------------------------------------------- */
word OpaalConfig::getCnfDayDurationHours() {
  return this->_cnfDayDurationHours;
}

/* -------------------------------------------------------------------- */
word OpaalConfig::getCnfMoonDurationHours() {
  return this->_cnfMoonDurationHours;
}

/* -------------------------------------------------------------------- */
float OpaalConfig::getCnfLampPower() {
  return this->_cnfLampPower;
}

/* -------------------------------------------------------------------- */
float OpaalConfig::getCnfLightTemperature() {
  return this->_cnfLightTemperature;
}

/* -------------------------------------------------------------------- */
void OpaalConfig::setCnfStartHour(word newStartHour) {
  this->_cnfStartHour = newStartHour;
}

/* -------------------------------------------------------------------- */
void OpaalConfig::setCnfStartMinute(word newStartMinute) {
  this->_cnfStartMinute = newStartMinute;
}

/* -------------------------------------------------------------------- */
void OpaalConfig::setCnfDayDurationHours(word newDayDurationHours) {
  this->_cnfDayDurationHours = newDayDurationHours;
}

/* -------------------------------------------------------------------- */
void OpaalConfig::setCnfMoonDurationHours(word newMoonDurationHours) {
  this->_cnfMoonDurationHours = newMoonDurationHours;
}

/* -------------------------------------------------------------------- */
void OpaalConfig::setCnfLampPower(float newLampPower) {
  this->_cnfLampPower = newLampPower;
}

/* -------------------------------------------------------------------- */
void OpaalConfig::setCnfLightTemperature(float newLightTemperature) {
  this->_cnfLightTemperature = newLightTemperature;
}

/* -------------------------------------------------------------------- */
void OpaalConfig::save() {
  eeprom_write_block(&this->_cnfStartHour,0,2);
  eeprom_write_block(&this->_cnfStartMinute,2,2);
  eeprom_write_block(&this->_cnfDayDurationHours,4,2);
  eeprom_write_block(&this->_cnfMoonDurationHours,6,2);
  eeprom_write_block(&this->_cnfLampPower,8,4);
  eeprom_write_block(&this->_cnfLightTemperature,12,4);
  delay(1000);
}

/* -------------------------------------------------------------------- */
void OpaalConfig::load() {
  eeprom_read_block(&this->_cnfStartHour,0,2);
  eeprom_read_block(&this->_cnfStartMinute,2,2);
  eeprom_read_block(&this->_cnfDayDurationHours,4,2);
  eeprom_read_block(&this->_cnfMoonDurationHours,6,2);
  eeprom_read_block(&this->_cnfLampPower,8,4);
  eeprom_read_block(&this->_cnfLightTemperature,12,4);
}
