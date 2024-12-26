#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>

#include "my_mqtt.h"
#include "_class_dsp.h"

extern bool new_data;
extern bool power_switch;

extern uint8_t global_brightness;
extern uint8_t brModeMinimumBrightness;
extern uint8_t brModeMinimumBrightnessPwm;

void plotBands();

extern long last_rf24_fps;
extern long last_fps;
// extern uint8_t trebleHue;
// extern uint8_t midHue;
// extern uint8_t bassHue;

extern uint32_t deltaMillis_lichtorgel;
extern uint16_t alarm_onTime;
extern uint16_t alarm_offTime;
extern uint16_t alarm_repeats;

#endif