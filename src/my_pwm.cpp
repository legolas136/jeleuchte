#include "my_pwm.h"

#define PWM_PIN_0 32

void MyPwm::setup()
{
  // configure LED PWM functionalitites
  ledcSetup(ledcChannel, myPwmFreq, myPwmResolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(PWM_PIN_0, ledcChannel);
}

void MyPwm::setBrightnessPercent(float input)
{
  if (input > 100)
  {
    input = 100;
  }
  else if (input < 0)
  {
    input = 0;
  }

  brightness = ((input * (pow(2, myPwmResolution))-1) / 100);
  update();
}

void MyPwm::setBrightness8bit(uint8_t input)
{

  brightness = ((input * (pow(2, myPwmResolution))-1) / 255);
  update();
}

void MyPwm::changeFreq(double input)
{
  // configure LED PWM functionalitites
  ledcSetup(ledcChannel, input, myPwmResolution);
  update();
}

void MyPwm::update()
{
  ledcWrite(ledcChannel, brightness);
}