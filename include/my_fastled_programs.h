#ifndef MY_LED_PROGRAMS_H
#define MY_LED_PROGRAMS_H

#include <Arduino.h>
#include "my_fastled_enums.h"
#include "my_fastled_init.h"
#include "my_fastled_helpers.h"
#include "globals.h"
#include "_class_dsp.h"

extern CRGB leds[NUM_LEDS];    // Initialize main LED object
extern CRGB ledsA[NUM_LEDS];   // Initialize temporary LED object A
extern CRGB ledsB[NUM_LEDS];   // Initialize temporary LED object B

void rainbow_wave(
    uint8_t thisSpeed,
    uint8_t deltaHue);
void rainbow_wave2(
    uint8_t thisSpeed,
    uint8_t deltaHue);
void static_color_fill(
    // set all LEDs to specified color
    uint8_t input_r = 0,
    uint8_t input_g = 0,
    uint8_t input_b = 0);
void static_color_fill_every_second(
    // set all LEDs to specified color
    uint8_t input_r = 0,
    uint8_t input_g = 0,
    uint8_t input_b = 0);
void static_color_fill_bed_rear(
    // set all LEDs to specified color
    uint8_t input_r = 0,
    uint8_t input_g = 0,
    uint8_t input_b = 0);
void blendedrainbowsA(uint8_t thisSpeed, uint8_t deltaHue);
void blendedrainbowsB(uint8_t thisSpeed, uint8_t deltaHue);
void blendedrainbows();



#endif