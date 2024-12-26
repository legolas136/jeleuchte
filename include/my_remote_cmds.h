#ifndef MY_REMOTE_CMDS_H
#define MY_REMOTE_CMDS_H

#include <Arduino.h>
#include "my_config.h"

extern my_preferences config;

void dimUp(uint8_t delta = 5);

void dimDown(uint8_t delta = 5);

void programIncrease();

void programDecrease();

#endif