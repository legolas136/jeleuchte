#ifndef MY_SPECIALS_H
#define MY_SPECIALS_H

#include <Arduino.h>
#include "globals.h"

void fps(const int seconds = 1);
void rf24_in_fps(const int seconds = 1);
void getFreeHeap();
String getChipID();
void printChipID();
void checkChipID();
void handle_error();

#endif