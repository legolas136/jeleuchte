#ifndef _CLASS_DAMPENEDVAL_H
#define _CLASS_DAMPENEDVAL_H

#include <Arduino.h>
#include "definitions.h"
#include "_class_dsp.h"

// extern PubSubClient mqttclient;

class DampenedVal
{
private:
public:
  uint16_t input = 0;
  float output;
  float reductor = 0.99f;
  float incrementor = 1.05f;
  unsigned long lastmillisTick = millis();
  unsigned long lastmicrosTick = micros();
  void setReductor(float input);
  void setIncrementor(float input);
  void setCacheTime(uint16_t input);
  uint8_t getInput();
  uint8_t getOutput();
  void tick(uint8_t time_base = 2);
  void tickMicroSeconds(uint16_t time_base = 2000);
  void tickMicroSecondsNew(uint16_t time_base = 2000);
};

class DampenedBands
{
private:
public:
  // uint16_t input[NUMBER_OF_BANDS] = {0};
  float output[NUMBER_OF_BANDS];
  float reductor[NUMBER_OF_BANDS] = {0.99f, 0.99f, 0.99f, 0.99f, 0.99f, 0.99f, 0.99f, 0.99f, 0.99f, 0.99f, 0.99f, 0.99f, 0.99f, 0.99f, 0.99f, 0.99f};
  float incrementor[NUMBER_OF_BANDS] = {1.05f};
  unsigned long lastmicrosTick[NUMBER_OF_BANDS] = {micros()};
  uint16_t bandLevelsDampened[NUMBER_OF_BANDS];
  uint16_t fallingspeed[NUMBER_OF_BANDS] = {5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000};

  void tick();
  void setFalligSpeed(uint8_t band, uint16_t falling_speed);
  void setReductor(float input);
  void setIncrementor(float input);
  void printOutput(uint16_t deltamillis);
  uint8_t getInput();
  uint8_t getOutput(uint8_t band);
};

#endif