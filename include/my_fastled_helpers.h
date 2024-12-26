#ifndef MY_FASTLED_HELPERS_H
#define MY_FASTLED_HELPERS_H

#include <Arduino.h>
#include "my_fastled_init.h"
#include "my_fastled_enums.h"
#include "my_config.h"
#include "my_fastled_programs.h"
#include "my_pwm.h"

extern CRGB leds[NUM_LEDS];    // Initialize main LED object
extern CRGB ledsA[NUM_LEDS];   // Initialize temporary LED object A
extern CRGB ledsB[NUM_LEDS];   // Initialize temporary LED object B
extern CRGB ledsTemp[NUM_LEDS];   // Initialize temporary LED object B

extern MyPwm MyPwm1;

extern my_preferences config;

void blendAnimations(
  uint8_t ratio = 127,
  CRGB (&inputA)[NUM_LEDS] = ledsA,
  CRGB (&inputB)[NUM_LEDS] = ledsB,
  CRGB (&output)[NUM_LEDS] = leds
);

void half_animation(
    // Shrink the animation to the first half of the stripe (last half will not be blanked!)
    CRGB (&input)[NUM_LEDS]
);

void shrink_animation(
    CRGB (&input)[NUM_LEDS],
    float divisor = 2.0f
);

    // Mirror (default: INNER_TO_OUTER)
void mirror(
    CRGB (&input)[NUM_LEDS],
    AnimationMirrorDirection animationDirection = INNER_TO_OUTER
);

void split_and_reverse_first_segment(
    CRGB (&input)[NUM_LEDS],
    uint16_t last_pixel_of_first_segment
);

void led_alarm_blink(
    uint8_t r = 255, 
    uint8_t g = 255, 
    uint8_t b = 255, 
    uint16_t on_time = 500, 
    uint16_t off_time = 500, 
    uint8_t repeats = 5
);

#endif