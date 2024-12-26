#include "my_fastled_programs_br.h"

// project related
// #include "_class_dsp.h"
// extern MSGEQ7_DSP dsp;
// end project-related

void gradientTrebleMiddle_BassOuter()
{
  uint8_t starthueBass = 224;
  uint8_t endhueBass = 20;
  uint8_t starthueTreble = 160;
  uint8_t endhueTreble = 96;

  blanken();
  uint8_t bassMapped = map(Bass.getOutput(), 0, 255, 0, config.num_leds_connected - 1);
  uint8_t trebleMapped = map(Treble.getOutput(), 0, 255, 0, config.num_leds_connected - 1);

  fill_gradient(
      leds,
      0,
      CHSV(starthueBass, 255, 255),
      bassMapped / 4,
      CHSV(endhueBass, 255, 255),
      SHORTEST_HUES);

  fill_gradient(
      leds,
      config.num_leds_connected - 1,
      CHSV(starthueBass, 255, 255),
      config.num_leds_connected - 1 - bassMapped / 4,
      CHSV(endhueBass, 255, 255),
      SHORTEST_HUES);

  fill_gradient(
      leds,
      (config.num_leds_connected - 1) / 2,
      CHSV(starthueTreble, 255, 255),
      ((config.num_leds_connected - 1) / 2) + trebleMapped / 4,
      CHSV(endhueTreble, 255, 255),
      SHORTEST_HUES);

  fill_gradient(
      leds,
      (config.num_leds_connected - 1) / 2,
      CHSV(starthueTreble, 255, 255),
      ((config.num_leds_connected - 1) / 2) - trebleMapped / 4,
      CHSV(endhueTreble, 255, 255),
      SHORTEST_HUES);
}

void gradientBassMiddle_TrebleOuter()
{
  uint8_t starthueBass = 224;
  uint8_t endhueBass = 20;
  uint8_t starthueTreble = 160;
  uint8_t endhueTreble = 96;

  blanken();

  uint8_t bassMapped = map(Bass.getOutput(), 0, 255, 0, config.num_leds_connected - 1);
  uint8_t trebleMapped = map(Treble.getOutput(), 0, 255, 0, config.num_leds_connected - 1);

  fill_gradient(
      leds,
      0,
      CHSV(starthueTreble, 255, 255),
      trebleMapped / 4,
      CHSV(endhueTreble, 255, 255),
      SHORTEST_HUES);

  fill_gradient(
      leds,
      config.num_leds_connected - 1,
      CHSV(starthueTreble, 255, 255),
      config.num_leds_connected - 1 - trebleMapped / 4,
      CHSV(endhueTreble, 255, 255),
      SHORTEST_HUES);

  fill_gradient(
      leds,
      (config.num_leds_connected - 1) / 2,
      CHSV(starthueBass, 255, 255),
      ((config.num_leds_connected - 1) / 2) + bassMapped / 4,
      CHSV(endhueBass, 255, 255),
      SHORTEST_HUES);

  fill_gradient(
      leds,
      (config.num_leds_connected - 1) / 2,
      CHSV(starthueBass, 255, 255),
      ((config.num_leds_connected - 1) / 2) - bassMapped / 4,
      CHSV(endhueBass, 255, 255),
      SHORTEST_HUES);
}

void bassGradient_TrebleStatic()
{
  uint8_t starthueBass = 224;
  uint8_t endhueBass = 20;

  blanken();

  uint8_t bassMapped = map(Bass.getOutput(), 0, 255, 0, 50);
  uint8_t midMapped = map(Mid.getOutput(), 0, 255, 0, 255);
  uint8_t trebleMapped = map(Treble.getOutput(), 0, 255, 0, 255);

  int trebleStart = 0;
  int trebleEnd = trebleStart + (config.num_leds_connected / 10);
  int midStart = trebleEnd + 1;
  int midEnd = midStart + (config.num_leds_connected / 7);

  for (int i = trebleStart; i < trebleEnd; i++)
  {

    leds[i] = CHSV(config.hue_treble, 255, trebleMapped);
    leds[(config.num_leds_connected - 1) - i] = CHSV(config.hue_treble, 255, trebleMapped);
  }

  for (int i = midStart; i < midEnd; i++)
  {

    leds[i] = CHSV(config.hue_mid, 255, midMapped);
    leds[(config.num_leds_connected - 1) - i] = CHSV(config.hue_mid, 255, midMapped);
  }

  fill_gradient(
      leds,
      (config.num_leds_connected) / 2,
      CHSV(starthueBass, 255, 255),
      (((config.num_leds_connected) / 2)) + (bassMapped * config.num_leds_connected) / 300,
      CHSV(endhueBass, 255, 255),
      SHORTEST_HUES);

  fill_gradient(
      leds,
      (config.num_leds_connected) / 2 - 1,
      CHSV(starthueBass, 255, 255),
      ((config.num_leds_connected) / 2 - 1) - (bassMapped * config.num_leds_connected) / 300,
      CHSV(endhueBass, 255, 255),
      SHORTEST_HUES);
}

void bassStatic_TrebleStatic()
{
  // uint8_t starthueBass = 224;
  // uint8_t endhueBass = 20;
  // uint8_t starthueTreble = 160;
  // uint8_t endhueTreble = 96;

  blanken();
  // uint16_t bassMapped = map(Bass.getOutput(), 0, 255, 0, 50);

  uint8_t bassMapped = map(Bass.getOutput(), 0, 255, 0, 255);
  uint8_t midMapped = map(Mid.getOutput(), 0, 255, 0, 255);
  uint8_t trebleMapped = map(Treble.getOutput(), 0, 255, 0, 255);

  int trebleStart = 0;
  int trebleEnd = trebleStart + (config.num_leds_connected / 10);
  int midStart = trebleEnd + 1;
  int midEnd = midStart + (config.num_leds_connected / 7);
  int bassStart = midEnd + 1;
  int bassEnd = config.num_leds_connected / 2;

  for (int i = trebleStart; i < trebleEnd; i++)
  {

    leds[i] = CHSV(config.hue_treble, 255, trebleMapped);
    leds[(config.num_leds_connected - 1) - i] = CHSV(config.hue_treble, 255, trebleMapped);
  }

  for (int i = midStart; i < midEnd; i++)
  {

    leds[i] = CHSV(config.hue_mid, 255, midMapped);
    leds[(config.num_leds_connected - 1) - i] = CHSV(config.hue_mid, 255, midMapped);
  }

  for (int i = bassStart; i < bassEnd; i++)
  {

    leds[i] = CHSV(config.hue_bass, 255, bassMapped);
    leds[(config.num_leds_connected - 1) - i] = CHSV(config.hue_bass, 255, bassMapped);
  }
}

void running_lights(
    CRGB (&input)[NUM_LEDS],

    AnimationDirection animationDirection,
    int shiftingIntervalInMs)
{
  static CRGB ledBuffer[NUM_LEDS];
  static unsigned long lastMillis;

  int hueoffset = 50;
  if (config.led_bed_mode)
  {
    split_and_reverse_first_segment(leds, 109);
  }

  if (millis() - lastMillis >= shiftingIntervalInMs)
  {
    lastMillis = millis();

    // calculate the new pixel
    uint8_t targethue = (dsp.bandLevelsReceived[0] - dsp.bandLevelsReceived[1]) + hueoffset * (200 / dsp.overallVolumeAverage);
    // uint8_t targethue = 255;
    // ledBuffer[0] = CHSV(targethue, 255, 255);
    ledBuffer[0] = CHSV(targethue, 255, Bass.getOutput());

    // shifting
    if (animationDirection == FORWARD)
    {
      int k = 1;
      float y = pow(0.1, 1.0 / config.num_leds_connected);
      for (int i = config.num_leds_connected - 1; i > 0; i--)
      { // shift old values further

        // ledBuffer[i] = ledBuffer[i - 1];

        if (i > 0)
        {
          // ledBuffer[i].r = uint8_t(ledBuffer[i - 1].r * 0.95);
          // ledBuffer[i].g = uint8_t(ledBuffer[i - 1].g * 0.95);
          // ledBuffer[i].b = uint8_t(ledBuffer[i - 1].b * 0.95);


          ledBuffer[i].r = uint8_t(ledBuffer[i - 1].r * y);
          ledBuffer[i].g = uint8_t(ledBuffer[i - 1].g * y);
          ledBuffer[i].b = uint8_t(ledBuffer[i - 1].b * y);
        }

        input[i] = ledBuffer[i];

        k++;
      }
    }
    if (animationDirection == BACKWARD)
    {

      for (int i = config.num_leds_connected - 1; i > 0; i--)
      {
        ledBuffer[i] = ledBuffer[i - 1];
        input[i] = ledBuffer[config.num_leds_connected - 1 - i];
      }
    }
  }
}

void running_lights_single_color(
    CRGB (&input)[NUM_LEDS],

    AnimationDirection animationDirection,
    int shiftingIntervalInMs)
{
  if (config.led_bed_mode)
  {
    split_and_reverse_first_segment(leds, 109);
  }
  static CRGB ledBuffer[NUM_LEDS];
  static unsigned long lastMillis;

  if (millis() - lastMillis >= shiftingIntervalInMs)
  {
    lastMillis = millis();

    // calculate the new pixel
    // uint8_t targethue = (dsp.bandLevelsReceived[0] - dsp.bandLevelsReceived[1]) + hueoffset * (200 / dsp.overallVolumeAverage);
    // uint8_t targethue = 255;
    uint8_t targethue = config.hue_bass;
    // ledBuffer[0] = CHSV(targethue, 255, 255);
    ledBuffer[0] = CHSV(targethue, 255, Bass.getOutput());

    // shifting
    if (animationDirection == FORWARD)
    {
      for (int i = config.num_leds_connected - 1; i > 0; i--)
      { // shift old values further
        ledBuffer[i] = ledBuffer[i - 1];
        input[i] = ledBuffer[i];
      }
    }
    if (animationDirection == BACKWARD)
    {
      for (int i = config.num_leds_connected - 1; i > 0; i--)
      {
        ledBuffer[i] = ledBuffer[i - 1];
        input[i] = ledBuffer[config.num_leds_connected - 1 - i];
      }
    }
  }
}

void running_lights_center_to_outside()
{
  running_lights(ledsA, FORWARD, config.deltamillis);
  // half_animation(leds);
  mirror(ledsA, INNER_TO_OUTER);
}

void running_lights_outside_to_center()
{
  running_lights(leds, FORWARD, config.deltamillis);
  // half_animation(leds);
  mirror(leds, OUTER_TO_INNER);
}

void running_lights_outside_to_center_double()
{
  running_lights(leds, FORWARD, config.deltamillis);
  // half_animation(leds);
  mirror(leds, OUTER_TO_INNER_DOUBLE);
}

void running_lights_single_color_center_to_outside()
{
  running_lights_single_color(ledsA, FORWARD, config.deltamillis);
  // half_animation(leds);
  mirror(ledsA, INNER_TO_OUTER);
}

void running_lights_single_color_outside_to_center()
{
  running_lights_single_color(leds, FORWARD, config.deltamillis);
  // half_animation(leds);
  mirror(leds, OUTER_TO_INNER);
}

void running_lights_single_color_outside_to_center_double()
{
  running_lights_single_color(leds, FORWARD, config.deltamillis);
  // half_animation(leds);
  mirror(leds, OUTER_TO_INNER_DOUBLE);
}
