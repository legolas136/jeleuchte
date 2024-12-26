#ifndef MY_FASTLED_HANDLE_H
#define MY_FASTLED_HANDLE_H

#include <Arduino.h>

#include "my_fastled_init.h"
#include "my_fastled_programs.h"
#include "my_fastled_programs_br.h"
#include "my_webserver.h"
#define TARGET_FPS 60

#include "globals.h"
#include "my_dampenedval_objects.h"
#include "config.h"
#include "my_pwm.h"


// #include "led_programs.h"
// #include "globals.h"
extern DampenedVal BrMode;
// extern int selectedProgram;
extern bool power_switch;
extern uint8_t led_alarm_active;

void programmSelect();
void ledHandle(uint16_t target_fps = 60);
#endif