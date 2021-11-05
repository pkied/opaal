/*
  opaal_lamp.h - Class for control led lamp in OPAAL project.
  Created by Paweł Kiedrzyński, September 28, 2021.
  Released into the public domain.
*/

#ifndef opaal_lamp_h
#define opaal_lamp_h

#include "opaal_channel.h"

#define CH_WHITE 0
#define CH_RED 1
#define CH_GREEN 2
#define CH_BLUE 3
#define CH_YELLOW 4
#define CHI_COUNT 5

#define COL_NIGHT 0
#define COL_SUNRISE 1
#define COL_SUNTOP 2
#define COL_SUNSET 3
#define COL_MOON 4
#define COLI_COUNT 5

static const byte c_lampChannelPins[CHI_COUNT] = { //w,r,g,b,y
    3, 10, 6, 9, 5
};

static const float c_lampColorProfiles[COLI_COUNT][CHI_COUNT] = { //w,r,g,b,y
    {0.0, 0.0, 0.0, 0.0, 0.0},    //NIGHT
    {0.1, 0.1, 0.06, 0.03, 0.4},  //SUNRISE
    {1.0, 1.0, 0.6, 0.3, 0.0},    //SUNTOP
    {0.1, 0.1, 0.06, 0.03, 0.4},  //SUNSET
    {0.01, 0.0, 0.0, 0.0, 0.0}    //MOON
};

static const float c_lampTemperatureProfiles[CHI_COUNT] = { //w,r,g,b,y
    0.0, -1.0, -0.2, 1.0, -0.5
};

class OpaalLamp {
  private:
    bool _on = true;
    float _power = 1.0;         //0 - off, 1 - full on
    float _temperature = 0.0;   //-1 - warmest, 1 - coolest
    byte _color = COL_NIGHT;
    OpaalChannel _channel[CHI_COUNT];
    void _adjustChannelPower(byte chi);
  public:
    void setOn(bool newOn);
    void setPower(float newPower);
    float getPower();
    void setTemperature(float newTemperature);
    void changeColor(byte newColor, unsigned long changeMillis);
    byte getColor();
    void begin();
    void run();
};
#endif
