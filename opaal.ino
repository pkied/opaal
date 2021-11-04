#include <Arduino.h>
#include "opaal_fan.h"
#include "opaal_lamp.h"
#include "opaal_scheduler.h"
#include "opaal_config.h"
#include "opaal_ui.h"

OpaalFan fan;
OpaalLamp lamp;
OpaalScheduler scheduler;
OpaalConfig conf;
OpaalUI ui;

void setup() {
  //test only ------------------------------------
  Serial.begin(9600);
  setTime(7,59,55,18,10,2021);
  RTC.set(now());
  //test end -------------------------------------
  
  fan.begin(37,32,11); //fan start temp, fan stop temp, pwm pin
  lamp.begin();
  scheduler.begin(&lamp);
  conf.begin();
  ui.begin(&fan, &conf, &lamp);
}

void loop() {
  fan.run();
  lamp.run();
  scheduler.run();
  ui.run();
}
