#include "my_fastled_programs.h"

void rainbow_wave(
    uint8_t thisSpeed,
    uint8_t deltaHue)
{                                                                   // The fill_rainbow call doesn't support brightness levels.
  uint8_t thisHue = beat8(thisSpeed, 255);                          // A simple rainbow march.
  fill_rainbow(leds, config.num_leds_connected, thisHue, deltaHue); // Use FastLED's fill_rainbow routine.
}

void rainbow_wave2(
    uint8_t thisSpeed,
    uint8_t deltaHue)
{                                                                   // The fill_rainbow call doesn't support brightness levels.
  uint8_t thisHue = beatsin8(thisSpeed, 0, 255);                    // A simple rainbow wave.
  fill_rainbow(leds, config.num_leds_connected, thisHue, deltaHue); // Use FastLED's fill_rainbow routine.
}

void static_color_fill(
    // set all LEDs to specified color
    uint8_t input_r,
    uint8_t input_g,
    uint8_t input_b)
{
  for (int i = 0; i < config.num_leds_connected; i++)
  {
    // leds[i].r = input_r;
    // leds[i].g = input_g;
    // leds[i].b = input_b;
    leds[i].r = config.fixed_color_r;
    leds[i].g = config.fixed_color_g;
    leds[i].b = config.fixed_color_b;
  }
}

void static_color_fill_every_second(
    // set all LEDs to specified color
    uint8_t input_r,
    uint8_t input_g,
    uint8_t input_b)
{
  for (int i = 0; i < config.num_leds_connected; i++)
  {
    if (i % 2 > 0)
    {
      leds[i].r = config.fixed_color_r;
      leds[i].g = config.fixed_color_g;
      leds[i].b = config.fixed_color_b;
    }
    else
    {
      leds[i].r = 0;
      leds[i].g = 0;
      leds[i].b = 0;
    }
  }
}

void static_color_fill_bed_rear(
    // set all LEDs to specified color
    uint8_t input_r,
    uint8_t input_g,
    uint8_t input_b)
{
  for (int i = 0; i < 109; i++)
  {
    if (i % 2 > 0)
    {
      leds[i].r = config.fixed_color_r;
      leds[i].g = config.fixed_color_g;
      leds[i].b = config.fixed_color_b;
    }
    else
    {
      leds[i].r = 0;
      leds[i].g = 0;
      leds[i].b = 0;
    }
  }
  for (int i = 109; i < config.num_leds_connected; i++)
  {
    leds[i].r = 0;
    leds[i].g = 0;
    leds[i].b = 0;
  }
}

void blendedrainbowsA(uint8_t thisSpeed, uint8_t deltaHue)
{
  uint8_t thisHue = beat8(thisSpeed, 255);                           // A simple rainbow march.
  fill_rainbow(ledsA, config.num_leds_connected, thisHue, deltaHue); // Use FastLED's fill_rainbow routine.
}

void blendedrainbowsB(uint8_t thisSpeed, uint8_t deltaHue)
{
  uint8_t thisHue = beatsin8(thisSpeed, 0, 255);                     // A simple rainbow wave.
  fill_rainbow(ledsB, config.num_leds_connected, thisHue, deltaHue); // Use FastLED's fill_rainbow routine.
}

void blendedrainbows()
{
  blendedrainbowsA(2, 1);
  blendedrainbowsB(5, 2);

  uint8_t ratio = 127; // Blend ratio (127 for constant 50%  /50%)

  for (int i = 0; i < config.num_leds_connected; i++)
  {                                             // Apply to all LEDS
    leds[i] = blend(ledsA[i], ledsB[i], ratio); // Blending of animation A and B with given ration
  }
}

// void blendAnimations(
//   uint8_t ratio,
//   CRGB (&inputA)[NUM_LEDS],
//   CRGB (&inputB)[NUM_LEDS],
//   CRGB (&output)[NUM_LEDS]
// )
// {
//   for (int i = 0; i < config.num_leds_connected; i++)
//   {                                             // Apply to all LEDS
//     output[i] = blend(inputA[i], inputB[i], ratio); // Blending of animation A and B with given ration
//   }
// }

// void half_animation(
//     // Shrink the animation to the first half of the stripe (last half will not be blanked!)
//     CRGB (&input)[NUM_LEDS])
// {
//   for (int i = 0; i < config.num_leds_connected / 2; i++)
//   {                          // Take half the count of config.num_leds_connected ...
//     input[i] = input[i * 2]; // ... and shrink to fit the first half                                                                           // Set the second half to black/off
//   }
// }

// void shrink_animation(
//     CRGB (&input)[NUM_LEDS],
//     float divisor
// )
// {
//   for (int i = 0; i < int(config.num_leds_connected / divisor); i++)
//   {
//     input[i] = input[int(i * divisor)];                                                                      // Set the second half to black/off
//   }
// }

// void mirror(
//     // Mirror (default: INNER_TO_OUTER)
//     CRGB (&input)[NUM_LEDS],
//     AnimationMirrorDirection animationDirection)
// {
//   // static CRGB temp[config.num_leds_connected];
//   // for (int i; i < config.num_leds_connected; i++)
//   // {
//   //   temp[i] = input[i];
//   // }
//   int num_leds_connected_even = config.num_leds_connected;

//   if(config.num_leds_connected % 2 > 0) num_leds_connected_even = config.num_leds_connected - 1;
//   if (animationDirection == INNER_TO_OUTER)
//   { // Mirror (outside to inside)
//     for (int i = 0; i < num_leds_connected_even / 2; i++)
//     {                                           // Duplicate and mirror the gradient (middle to outside)
//       leds[num_leds_connected_even / 2 + i] = input[i]; // Move the first half to the second
//       leds[num_leds_connected_even / 2 -1 - i] = input[i]; // Copy the second half to first half, starting from the middle
//     }
//   }

//   if (animationDirection == OUTER_TO_INNER)
//   { // Mirror (inside to outside)
//     for (int i = 0; i < config.num_leds_connected / 2; i++)
//     { // Copy the first half to the second, starting from the end towards the middle
//       input[config.num_leds_connected - 1 - i] = input[i];
//     }
//   }

//   if (animationDirection == OUTER_TO_INNER_DOUBLE)
//   { // Mirror (outside to inside)
//     for (int i = 0; i < config.num_leds_connected / 2; i++)
//     {                                                        // Duplicate and mirror the gradient (middle to outside)
//       input[config.num_leds_connected / 2 + i] = input[i];                    // Move the first half to the second
//       input[config.num_leds_connected / 2 - 1 - i] = input[config.num_leds_connected / 2 + i]; // Copy the second half to first half, starting from the middle
//     }
//   }
// }
