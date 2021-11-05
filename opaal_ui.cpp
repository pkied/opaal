/*
  opaal_ui.cpp - Class for control UI in OPAAL project.
  Created by Paweł Kiedrzyński, October 25, 2021.
  Released into the public domain.
*/

#include "opaal_ui.h"

/* -------------------------------------------------------------------- */
OpaalUI::OpaalUI() : _modeButton(7), _selectButton(8) {
}

/* -------------------------------------------------------------------- */
void OpaalUI::begin(OpaalFan *newFan, OpaalConfig *newConf, OpaalLamp *newLamp) {
  this->_fan = newFan;
  this->_conf = newConf;
  this->_lamp = newLamp;
  Wire.begin();
  Wire.setClock(400000L);
  this->_modeButton.begin();
  this->_selectButton.begin();
  this->_oled.begin(&Adafruit128x64, 0x3C, -1);
  this->_oled.clear();
}

/* -------------------------------------------------------------------- */
void OpaalUI::run() {
  this->_modeButton.read();
  this->_selectButton.read();

  if (this->_modeButton.wasReleased()) {
    this->_oled.clear();
    this->_mode = this->_mode+1;
    if (this->_mode > 9) this->_mode = 0;    
  }
  
  this->_mvStatusBar();

  char vbuf[10];
  if (this->_mode == 0) this->_mvClock();
  if (this->_mode == 1) {
    sprintf(vbuf,"%02u:%02u", hour(), minute()); 
    this->_mvSettings("Time settings: hour", vbuf);
  }
  if (this->_mode == 2) {
    sprintf(vbuf,"%02u:%02u", hour(), minute()); 
    this->_mvSettings("Time settings: minute", vbuf);
  }
  if (this->_mode == 3) {
    sprintf(vbuf,"%02u:%02u", this->_conf->getCnfStartHour(), this->_conf->getCnfStartMinute()); 
    this->_mvSettings("Start time: hour", vbuf);
  }
  if (this->_mode == 4) {
    sprintf(vbuf,"%02u:%02u", this->_conf->getCnfStartHour(), this->_conf->getCnfStartMinute()); 
    this->_mvSettings("Start time: minute", vbuf);
  }
  if (this->_mode == 5) {
    sprintf(vbuf,"%02u", this->_conf->getCnfDayDurationHours()); 
    this->_mvSettings("Day duration: hours", vbuf);
  }
  if (this->_mode == 6) {
    sprintf(vbuf,"%02u", this->_conf->getCnfMoonDurationHours()); 
    this->_mvSettings("Moon duration: hours", vbuf);
  }
  if (this->_mode == 7) {
    sprintf(vbuf,"%u%%", this->_conf->getCnfLampPower()); 
    this->_mvSettings("Lamp power", vbuf);
  }
  if (this->_mode == 8) {
    char flt[] = "W-----------C"; byte pos = (byte)((this->_conf->getCnfLightTemperature()+1.0)*5.0)+1; flt[pos] = '|';
    sprintf(vbuf,"%s", flt); 
    this->_mvSettings("Light temperature", vbuf);
  }
  if (this->_mode == 9) {
    this->_mvSettings("Save settings?", "NO");
  }

}

/* -------------------------------------------------------------------- */
void OpaalUI::_mvSettings(char *title, char *value, char *prefix = "", char *postfix = "") {
  this->_oled.setFont(Callibri11);
  this->_oled.setCursor(0,2);
  this->_oled.print(title);  
  this->_oled.setFont(CalLite24);
  this->_oled.setCursor(0,4);
  this->_oled.print(prefix);
  this->_oled.print(value);
  this->_oled.print(postfix);
  this->_oled.print("  ");
}

/* -------------------------------------------------------------------- */
void OpaalUI::_mvStatusBar() {
  char colName[][10] = {"Night", "Sunrise", "Day", "Sunset", "Moon"};
  this->_oled.setFont(Callibri11);
  this->_oled.setCursor(0,0);
  this->_oled.print(colName[this->_lamp->getColor()]);
  this->_oled.print(" ");
  this->_oled.print((byte)(this->_conf->getCnfLampPower()*100));
  this->_oled.print("%");

  byte temp = round(RTC.temperature() / 4.0);
  this->_oled.print(" ");
  this->_oled.print(temp);
  this->_oled.print("oC");
  if (this->_fan->isOn()) this->_oled.print("~");  
};

/* -------------------------------------------------------------------- */
void OpaalUI::_mvClock() {
  char time_buf[5]; 
  sprintf(time_buf,"%02u:%02u ", hour(), minute()); 
  this->_oled.setFont(CalLite24);
  this->_oled.setCursor(38,3);
  this->_oled.print(time_buf);
};
