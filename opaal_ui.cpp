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
void OpaalUI::begin(OpaalFan *newFan, OpaalConfig *newConf, OpaalLamp *newLamp, OpaalScheduler *newScheduler) {
  this->_fan = newFan;
  this->_conf = newConf;
  this->_lamp = newLamp;
  this->_scheduler = newScheduler;
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
    if (this->_mode > 11) this->_mode = 0;    
  }

  if (this->_selectButton.wasReleased()) {
    if (this->_mode == 1) { word h=hour()+1; if (h > 23) h = 0; setTime(h,minute(),00,1,1,2022); }
    if (this->_mode == 2) { word m=minute()+1; if (m > 59) m = 0; setTime(hour(),m,00,1,1,2022); }
    if (this->_mode == 3) { word h=this->_conf->getCnfStartHour()+1; if (h > 10) h = 4; this->_conf->setCnfStartHour(h); this->_scheduler->simpleSetup(this->_conf->getCnfStartHour(), this->_conf->getCnfStartMinute(), this->_conf->getCnfDayDurationHours(), this->_conf->getCnfMoonDurationHours(), this->_conf->getCnfTransitionMinutes()*60000); }
    if (this->_mode == 4) { word m=this->_conf->getCnfStartMinute()+1; if (m > 59) m = 0; this->_conf->setCnfStartMinute(m); this->_scheduler->simpleSetup(this->_conf->getCnfStartHour(), this->_conf->getCnfStartMinute(), this->_conf->getCnfDayDurationHours(), this->_conf->getCnfMoonDurationHours(), this->_conf->getCnfTransitionMinutes()*60000); }
    if (this->_mode == 5) { word h=this->_conf->getCnfDayDurationHours()+1; if (h > 12) h = 4; this->_conf->setCnfDayDurationHours(h); this->_scheduler->simpleSetup(this->_conf->getCnfStartHour(), this->_conf->getCnfStartMinute(), this->_conf->getCnfDayDurationHours(), this->_conf->getCnfMoonDurationHours(), this->_conf->getCnfTransitionMinutes()*60000); }
    if (this->_mode == 6) { word h=this->_conf->getCnfMoonDurationHours()+1; if (h > 4) h = 1; this->_conf->setCnfMoonDurationHours(h); this->_scheduler->simpleSetup(this->_conf->getCnfStartHour(), this->_conf->getCnfStartMinute(), this->_conf->getCnfDayDurationHours(), this->_conf->getCnfMoonDurationHours(), this->_conf->getCnfTransitionMinutes()*60000); }
    if (this->_mode == 7) { float p=this->_conf->getCnfLampPower()+0.1; if (p > 1.0001) p = 0.0; this->_conf->setCnfLampPower(p); this->_lamp->setPower(p); }
    if (this->_mode == 8) { float t=this->_conf->getCnfLightTemperature()+0.2; if (t > 1.0) t = -1.0; this->_conf->setCnfLightTemperature(t); this->_lamp->setTemperature(t); }
    if (this->_mode == 9) { word t=this->_conf->getCnfTransitionMinutes()+1; if (t > 15) t = 1; this->_conf->setCnfTransitionMinutes(t); this->_scheduler->setTransitionTimeMillis(t*60000);}
    if (this->_mode == 10) { word t=this->_conf->getCnfScreenBlankMinutes()+1; if (t > 5) t = 1; this->_conf->setCnfScreenBlankMinutes(t); this->_screenBlankTime = t*60000; }
    if (this->_mode == 11) { this->_conf->save(); this->_mvSave(); this->_mode = 0;}
  }
  
  this->_mvStatusBar();

  char vbuf[10];
  if (this->_mode == 0) this->_mvClock();
  if (this->_mode == 1) { sprintf(vbuf,"%02u:%02u", hour(), minute()); this->_mvSettings("Time settings (hour)", vbuf); }
  if (this->_mode == 2) { sprintf(vbuf,"%02u:%02u", hour(), minute()); this->_mvSettings("Time settings (minute)", vbuf); }
  if (this->_mode == 3) { sprintf(vbuf,"%02u:%02u", this->_conf->getCnfStartHour(), this->_conf->getCnfStartMinute()); this->_mvSettings("Start time (hour)", vbuf); }
  if (this->_mode == 4) { sprintf(vbuf,"%02u:%02u", this->_conf->getCnfStartHour(), this->_conf->getCnfStartMinute()); this->_mvSettings("Start time (minute)", vbuf); }
  if (this->_mode == 5) { sprintf(vbuf,"%02u h", this->_conf->getCnfDayDurationHours()); this->_mvSettings("Day duration", vbuf); }
  if (this->_mode == 6) { sprintf(vbuf,"%02u h", this->_conf->getCnfMoonDurationHours()); this->_mvSettings("Moon duration", vbuf); }
  if (this->_mode == 7) { byte flp = (byte)(this->_conf->getCnfLampPower() * 100); sprintf(vbuf,"%u%%", flp); this->_mvSettings("Lamp power", vbuf); }
  if (this->_mode == 8) { char flt[] = "W-----------C"; byte pos = (byte)((this->_conf->getCnfLightTemperature()+1.0)*5.1)+1; flt[pos] = '|'; sprintf(vbuf,"%s", flt); this->_mvSettings("Light temperature", vbuf); }
  if (this->_mode == 9) { sprintf(vbuf,"%02u m", this->_conf->getCnfTransitionMinutes()); this->_mvSettings("Light color transition time", vbuf); }
  if (this->_mode == 10) { sprintf(vbuf,"%02u m", this->_conf->getCnfScreenBlankMinutes()); this->_mvSettings("Screen blank time", vbuf); }
  if (this->_mode == 11) { this->_mvSettings("Save settings?", "No"); }
}

/* -------------------------------------------------------------------- */
void OpaalUI::_mvSave() {
  this->_mvSettings("Save settings?", "Yes");
  delay(1000);
  this->_oled.clear();
  delay(1000);
}

/* -------------------------------------------------------------------- */
void OpaalUI::_mvSettings(char *title, char *value, char *prefix = "", char *postfix = "") {
  this->_oled.setFont(Callibri11);
  this->_oled.setCursor(0,2);
  this->_oled.print(title);  
  this->_oled.clearToEOL();
  this->_oled.setFont(CalLite24);
  this->_oled.setCursor(0,4);
  this->_oled.print(prefix);
  this->_oled.print(value);
  this->_oled.print(postfix);
  this->_oled.clearToEOL();
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
  this->_oled.clearToEOL();
};

/* -------------------------------------------------------------------- */
void OpaalUI::_mvClock() {
  char time_buf[5]; 
  sprintf(time_buf,"%02u:%02u ", hour(), minute()); 
  this->_oled.setFont(CalLite24);
  this->_oled.setCursor(38,3);
  this->_oled.print(time_buf);
};
