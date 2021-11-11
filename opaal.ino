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
  fan.begin(37,34,11); //fan start temp, fan stop temp, pwm pin
  lamp.begin();
  scheduler.begin(&lamp);
  conf.begin();
  ui.begin(&fan, &conf, &lamp, &scheduler);

  conf.load();
  scheduler.simpleSetup(conf.getCnfStartHour(), conf.getCnfStartMinute(), conf.getCnfDayDurationHours(), conf.getCnfMoonDurationHours(), conf.getCnfTransitionMinutes()*60000);
  lamp.setPower(conf.getCnfLampPower());
  lamp.setTemperature(conf.getCnfLightTemperature());
  scheduler.setTransitionTimeMillis(conf.getCnfTransitionMinutes()*60000);

  //setTime(7,59,55,18,10,2021); RTC.set(now()); //testing purpose only

}

void loop() {
  fan.run();
  lamp.run();
  scheduler.run();
  ui.run();
}
