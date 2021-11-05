/*
  opaal_ui.h - Class for control UI in OPAAL project.
  Created by Paweł Kiedrzyński, October 25, 2021.
  Released into the public domain.
*/

#ifndef opaal_ui_h
#define opaal_ui_h

#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "opaal_fan.h"
#include "opaal_config.h"
#include "opaal_lamp.h"
#include <JC_Button.h>
#include <DS3232RTC.h>

class OpaalUI {
  private:
    Button _modeButton;
    Button _selectButton;
    SSD1306AsciiWire _oled;
    byte _mode = 0;
    void _mvStatusBar();
    void _mvClock();
    void _mvTimeHour();
    void _modeTitle(char *title);
    void _mvSettings(char *title, char *value, char *prefix = "", char *postfix = ""); 
    OpaalFan *_fan;
    OpaalConfig *_conf;
    OpaalLamp *_lamp;
  public:
    OpaalUI();
    void begin(OpaalFan *newFan, OpaalConfig *newConf, OpaalLamp *newLamp);
    void run();
};
#endif
