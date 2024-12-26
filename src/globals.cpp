#include "globals.h"

extern PubSubClient mqttclient;
extern MSGEQ7_DSP dsp;

bool new_data = false;
bool power_switch = 1;
uint8_t led_alarm_active = false;
uint8_t brModeMinimumBrightness = 20;
uint8_t brModeMinimumBrightnessPwm = 20;

long last_rf24_fps = 0;
long last_fps = 0;
uint8_t trebleHue = 127;
uint8_t midHue = 190;
uint8_t bassHue = 50;

uint32_t deltaMillis_lichtorgel = 25;

uint16_t alarm_onTime = 1000;
uint16_t alarm_offTime = 1000;
uint16_t alarm_repeats = 10;

