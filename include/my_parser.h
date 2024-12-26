#pragma once

#include <Arduino.h>
// #include "globals.h"
#include "_class_dsp.h"
extern MSGEQ7_DSP dsp;
// #include "specials.h"

void parseBands(char buf[33]);
void parsePayload(char buf[33]);
void interpretParsedVariable(char nam[32], char val[32]);
void parseMisc(char buf[32]);
void parseVariable(char buf[32]);