#ifndef MY_FASTLED_INIT_H
#define MY_FASTLED_INIT_H

#define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_INTERNAL

#include <Arduino.h>
#include <FastLED.h>
// #include "globals.h"
#include "my_config.h"

extern my_preferences config;

// extern int selectedProgram;

#define NUM_LEDS 300 // Number of LED's max
// #define NUM_LEDS 216    // Number of LED's kueche
// #define NUM_LEDS 61    // Number of LED's andere

#define LED_PWR 33      // Output for MosFET to cut-off LEDs & Data GND to save power
#define LED_DT 13       // Serial data pin
#define COLOR_ORDER GRB // It's GRB for WS2812B and GBR for APA102
#define LED_TYPE WS2813 // What kind of strip are you using (APA102, WS2801 or WS2812B)?

struct FastLEDSettings
// Struct to hold config. Types 'byte' und 'word' don't work!
{
  uint8_t amount_of_vislinks_found;
  IPAddress ips[255];
  uint16_t ports[255];
  String descriptions[255];
};

struct LedTargetSettings
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t brightness;
};

// extern FastLEDSettings ledSettings;

// extern uint16_t num_leds_connected;

extern CRGB leds[NUM_LEDS];  // Initialize main LED object
extern CRGB ledsA[NUM_LEDS]; // Initialize temporary LED object A
extern CRGB ledsB[NUM_LEDS]; // Initialize temporary LED object B

void fastled_init();
void blanken(
    // blank all LEDs
    CRGB (&destination)[NUM_LEDS] = leds,
    int startled = 0,
    int endled = NUM_LEDS - 1);
void ledsOff();
void setGlobalBrightness(int input);
void setProgram(int input);
#endif