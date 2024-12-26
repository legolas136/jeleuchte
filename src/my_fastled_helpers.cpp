#include "my_fastled_helpers.h"

void blendAnimations(
    uint8_t ratio,
    CRGB (&inputA)[NUM_LEDS],
    CRGB (&inputB)[NUM_LEDS],
    CRGB (&output)[NUM_LEDS])
{
  for (int i = 0; i < config.num_leds_connected; i++)
  {                                                 // Apply to all LEDS
    output[i] = blend(inputA[i], inputB[i], ratio); // Blending of animation A and B with given ration
  }
}

void half_animation(
    // Shrink the animation to the first half of the stripe (last half will not be blanked!)
    CRGB (&input)[NUM_LEDS])
{
  for (int i = 0; i < config.num_leds_connected / 2; i++)
  {                          // Take half the count of config.num_leds_connected ...
    input[i] = input[i * 2]; // ... and shrink to fit the first half                                                                           // Set the second half to black/off
  }
}

void shrink_animation(
    CRGB (&input)[NUM_LEDS],
    float divisor)
{
  for (int i = 0; i < int(config.num_leds_connected / divisor); i++)
  {
    input[i] = input[int(i * divisor)]; // Set the second half to black/off
  }
}

void mirror(
    CRGB (&input)[NUM_LEDS],
    AnimationMirrorDirection animationDirection)
{
  // static CRGB temp[config.num_leds_connected];
  // for (int i; i < config.num_leds_connected; i++)
  // {
  //   temp[i] = input[i];
  // }
  int num_leds_connected_even = config.num_leds_connected;

  if (config.num_leds_connected % 2 > 0)
    num_leds_connected_even = config.num_leds_connected - 1;
  if (animationDirection == INNER_TO_OUTER)
  { // Mirror (outside to inside)
    for (int i = 0; i < num_leds_connected_even / 2; i++)
    {                                                       // Duplicate and mirror the gradient (middle to outside)
      leds[num_leds_connected_even / 2 + i] = input[i];     // Move the first half to the second
      leds[num_leds_connected_even / 2 - 1 - i] = input[i]; // Copy the second half to first half, starting from the middle
    }
  }

  if (animationDirection == OUTER_TO_INNER)
  { // Mirror (inside to outside)
    for (int i = 0; i < config.num_leds_connected / 2; i++)
    { // Copy the first half to the second, starting from the end towards the middle
      input[config.num_leds_connected - 1 - i] = input[i];
    }
  }

  if (animationDirection == OUTER_TO_INNER_DOUBLE)
  { // Mirror (outside to inside)
    for (int i = 0; i < config.num_leds_connected / 2; i++)
    {                                                                                          // Duplicate and mirror the gradient (middle to outside)
      input[config.num_leds_connected / 2 + i] = input[i];                                     // Move the first half to the second
      input[config.num_leds_connected / 2 - 1 - i] = input[config.num_leds_connected / 2 + i]; // Copy the second half to first half, starting from the middle
    }
  }
}

void split_and_reverse_first_segment(
    CRGB (&input)[NUM_LEDS],
    uint16_t last_pixel_of_first_segment)
{
  for (int i = 0; i < last_pixel_of_first_segment; i++)
  { //
    ledsTemp[i] = input[i];
  }

  for (int i = 0; i < last_pixel_of_first_segment; i++)
  { //
    input[i] = ledsTemp[last_pixel_of_first_segment - i];
  }
}

void led_alarm_blink(uint8_t r, uint8_t g, uint8_t b, uint16_t on_time, uint16_t off_time, uint8_t repeats)
{
  FastLED.setBrightness(0);
  FastLED.show();
  delay(200);
  for (int i = 0; i < repeats; i++)
  {
    FastLED.setBrightness(255);
    MyPwm1.setBrightnessPercent(100);
    for (int i = 0; i < config.num_leds_connected; i++)
    {
      leds[i].r = r;
      leds[i].g = g;
      leds[i].b = b;
    }
    FastLED.show();
    delay(on_time);

    for (int i = 0; i < config.num_leds_connected; i++)
    {
      leds[i].r = 0;
      leds[i].g = 0;
      leds[i].b = 0;
    }
    FastLED.show();
    delay(off_time);
  }
}

// config.num_leds_connected