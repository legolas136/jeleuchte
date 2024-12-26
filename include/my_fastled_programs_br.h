#ifndef MY_LED_PROGRAMS_BR_H
#define MY_LED_PROGRAMS_BR_H


#define READINGS_PER_SECOND 200 // Must match with the amount of readings sent by master

#include <Arduino.h>
#include "my_fastled_init.h"
#include "my_fastled_programs.h"
#include "globals.h"
#include "_class_dsp.h"
#include "my_dampenedval_objects.h"



extern CRGB leds[NUM_LEDS];    // Initialize main LED object
extern CRGB ledsA[NUM_LEDS];   // Initialize temporary LED object A
extern CRGB ledsB[NUM_LEDS];   // Initialize temporary LED object B

void gradientTrebleMiddle_BassOuter();
void gradientBassMiddle_TrebleOuter();
void bassGradient_TrebleStatic();
void bassStatic_TrebleStatic();
// static CRGB temp[num_leds_connected];
void running_lights(
    CRGB (&input)[NUM_LEDS] = leds,
    AnimationDirection animationDirection = FORWARD,
    int shiftingIntervalInMs = 10);
void running_lights_single_color(
    CRGB (&input)[NUM_LEDS] = leds,
    AnimationDirection animationDirection = FORWARD,
    int shiftingIntervalInMs = 10);
void running_lights_center_to_outside();
void running_lights_outside_to_center();
void running_lights_outside_to_center_double();
void running_lights_single_color_center_to_outside();
void running_lights_single_color_outside_to_center();
void running_lights_single_color_outside_to_center_double();
#endif