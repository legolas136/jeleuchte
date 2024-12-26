#ifndef MY_PWM_H
#define MY_PWM_H

#include "my_preferences.h"
extern my_preferences config;





class MyPwm
{
private:
public:
    uint8_t ledcChannel = 0;
    double myPwmFreq = 500;
    uint8_t myPwmResolution = 10;
    void setup();
    uint16_t brightness = 1023;
    void setBrightnessPercent(float input);
    void setBrightness8bit(uint8_t input);
    void update();
    void changeFreq(double input);
//   void setIncrementor(float input);
//   void setCacheTime(uint16_t input);
//   uint8_t getInput();
//   uint8_t getOutput();
//   void tick(uint8_t time_base = 2);
//   void tickMicroSeconds(uint16_t time_base = 2000);
//   void tickMicroSecondsNew(uint16_t time_base = 2000);
};

#endif