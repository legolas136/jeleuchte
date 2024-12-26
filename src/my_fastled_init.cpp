#include "my_fastled_init.h"

extern bool power_switch;
// FastLEDSettings ledSettings;

// uint16_t num_leds_connected = 60;

CRGB leds[NUM_LEDS];  // Initialize main LED object
CRGB ledsA[NUM_LEDS]; // Initialize temporary LED object A
CRGB ledsB[NUM_LEDS]; // Initialize temporary LED object B
CRGB ledsTemp[NUM_LEDS]; // Initialize temporary LED object B

LedTargetSettings staticColors;

void fastled_init()
{
  // needed for fastled_handle:moveStaticColorsToTarget()
  staticColors.r = config.fixed_color_r;
  staticColors.g = config.fixed_color_g;
  staticColors.b = config.fixed_color_b;

  if (config.led_color_order == 0)
  {
    LEDS.addLeds<LED_TYPE, LED_DT, GRB>(leds, NUM_LEDS);
  }
  else if (config.led_color_order == 1)
  {
    LEDS.addLeds<LED_TYPE, LED_DT, RGB>(leds, NUM_LEDS);
  }
  else if (config.led_color_order == 2)
  {
    LEDS.addLeds<LED_TYPE, LED_DT, GBR>(leds, NUM_LEDS);
  }
  FastLED.setBrightness(255);
  // FastLED.setMaxPowerInVoltsAndMilliamps(12, 10000);              // FastLED power management set at 5V, 500mA
  FastLED.show();
}

void blanken(
    // blank all LEDs
    CRGB (&destination)[NUM_LEDS],
    int startled,
    int endled)
{
  for (int i = startled; i < endled; i++)
  {
    destination[i] = CRGB(0, 0, 0);
  }
}

void ledsOff()
{
  power_switch = false;
  blanken();
  FastLED.show();
  FastLED.show();
  // mqttclient.publish("test", "test");
}

void setGlobalBrightness(int input)
{
  config.global_brightness = input;
}

void setProgram(int input)
{
  char program_as_char[4];
  sprintf(program_as_char, "%d", input);
  Serial.println(program_as_char);
  config.program = input;
}