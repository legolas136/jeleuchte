#include "my_fastled_handle.h"

// extern void static_color_fill(uint8_t,uint8_t,uint8_t);

// int selectedProgram = 6;
// selectedProgram = config.program;

extern MyPwm MyPwm1;
extern LedTargetSettings staticColors;

void programmSelect()
{
  switch (config.program)
  {
  case 1:
  {
    rainbow_wave2(10, 120);
    break;
  }
  case 2:
    blendedrainbows();
    break;
  case 3:
  {
    gradientTrebleMiddle_BassOuter();
    break;
  }
  case 4:
  {
    gradientBassMiddle_TrebleOuter();
    break;
  }
  case 5:
  {
    bassGradient_TrebleStatic();
    break;
  }
  case 6:
  {
    static_color_fill(123, 123, 123);
    break;
  }
  case 7:
  {
    running_lights(leds, FORWARD, config.deltamillis);
    break;
  }
  case 8:
  {
    running_lights_center_to_outside();
    break;
  }
  case 9:
  {
    running_lights_outside_to_center();
    break;
  }
  case 10:
  {
    running_lights_outside_to_center_double();
    break;
  }
  case 11:
  {
    bassStatic_TrebleStatic();
    break;
  }

  case 12:
  {
    if (config.gradient_color_1_h < config.gradient_color_2_h)
    {
      fill_gradient(
          leds,
          0,
          CHSV(config.gradient_color_1_h, config.gradient_color_1_s, config.gradient_color_1_v),
          config.num_leds_connected,
          CHSV(config.gradient_color_2_h, config.gradient_color_2_s, config.gradient_color_2_v),
          FORWARD_HUES);
    }
    else
    {
      fill_gradient(
          leds,
          0,
          CHSV(config.gradient_color_1_h, config.gradient_color_1_s, config.gradient_color_1_v),
          config.num_leds_connected,
          CHSV(config.gradient_color_2_h, config.gradient_color_2_s, config.gradient_color_2_v),
          BACKWARD_HUES);
    }

    break;
  }

  case 13:
  {
    fill_gradient(
        leds,
        0,
        // CHSV(255, 255, 255),
        CHSV(beatsin8(6, 220, 255), 255, beatsin8(13, 200, 255)),
        config.num_leds_connected,
        CHSV(beatsin8(5, 220, 255), 255, beatsin8(15, 200, 255)),
        SHORTEST_HUES);
    break;
  }

  case 14:
  {
    running_lights_single_color(leds, FORWARD, config.deltamillis);
    break;
  }

  case 15:
  {
    static_color_fill_bed_rear();
    break;
  }

  case 16:
  {
    static_color_fill_every_second(123, 123, 123);
    break;
  }

  case 17:
  {
    running_lights_single_color_center_to_outside();
    break;
  }

  case 18:
  {
    running_lights_single_color_outside_to_center();
    break;
  }

  case 19:
  {
    running_lights_single_color_outside_to_center_double();
    break;
  }

  case 20:
  {
    bassStatic_TrebleStatic();
    break;
  }

  default:
#ifdef SERIAL_DEBUG
    // Serial.println("Error: No program chosen!");
#endif
    break;
  }
}

// bool dim2off_active = false;

// void dim2off_tick(unsigned long time_in_ms)
// {
//   static unsigned long lastmillis = millis();

//   if (dim2off_active)
//   {
//     if ((millis() - lastmillis >= (time_in_ms / config.global_brightness)) && config.global_brightness > 0)
//     {
//       config.global_brightness--;
//     }
//     else
//     {
//       power_switch = false;
//       config.global_brightness = 255;
//     }
//   }
// }

void moveStaticColorsToTarget()
{
  static unsigned long lastmillis = millis();
  if (millis() - lastmillis >= 1)
  {
    lastmillis = millis();
    if (staticColors.r != config.fixed_color_r)
    {
      if (staticColors.r - config.fixed_color_r > 0)
      {
        config.fixed_color_r++;
      }
      else
      {
        config.fixed_color_r--;
      }
    }
    if (staticColors.g != config.fixed_color_g)
    {
      if (staticColors.g - config.fixed_color_g > 0)
      {
        config.fixed_color_g++;
      }
      else
      {
        config.fixed_color_g--;
      }
    }
    if (staticColors.b != config.fixed_color_b)
    {
      if (staticColors.b - config.fixed_color_b > 0)
      {
        config.fixed_color_b++;
      }
      else
      {
        config.fixed_color_b--;
      }
    }
  }
}

void ledHandle(uint16_t target_fps)
{
  moveStaticColorsToTarget();
  uint8_t intern_brightness = 255;
  uint8_t intern_brightness_pwm = 255;
  static long lastmillis = millis(); // Timestamp for target fps
  programmSelect();                  // Run the selected animation
                                     // const uint16_t target_fps = TARGET_FPS;

  if (power_switch == false)
  { // Check power switch status
    blanken();
    FastLED.show();
    FastLED.show();
    MyPwm1.setBrightnessPercent(0);
  }
  else
  {
    if (dsp.brModeOn == 1)
    { // If Beat-reactive mode is enabled
      intern_brightness = map(BrMode.getOutput(), 0, 255, brModeMinimumBrightness, 255);
    }
    else
    {
      intern_brightness = 255;
    }

    if (dsp.brModePwmOn == 1)
    { // If Beat-reactive mode is enabled
      intern_brightness_pwm = map(BrMode.getOutput(), 0, 255, brModeMinimumBrightnessPwm, 255);

      // MyPwm1.setBrightness8bit(config.global_brightness * intern_brightness_pwm / 255);
      ;
    }
    else
    {
      intern_brightness_pwm = 255;
    }

    FastLED.setBrightness(config.global_brightness * intern_brightness / 255); // Set brightness to all LEDs
    MyPwm1.setBrightnessPercent(config.pwm_brightness * intern_brightness_pwm / 255);

    // split and reverse first xxx pixel
    if (config.led_bed_mode)
    {
      split_and_reverse_first_segment(leds, 109);
    }

    if (millis() - lastmillis >= 1000 / target_fps)
    { // Run this part with a target fps
      lastmillis = millis();
      if (power_switch)
        FastLED.show();
    } // Update all LEDs

    if (power_switch == false)
    { // Check power switch status
      blanken();
      FastLED.show();
      FastLED.show();
      MyPwm1.setBrightnessPercent(0);
    }
  }
  if (led_alarm_active > 0)
  {
    switch (led_alarm_active)
    {
    case (1):
      led_alarm_blink(255, 255, 255, 200, 200, 10);
      led_alarm_active = false;
      break;
    case (2):
      led_alarm_blink(config.gradient_color_2_h, config.gradient_color_2_s, config.gradient_color_2_v, alarm_onTime, alarm_offTime, alarm_repeats);
      led_alarm_active = false;
      break;
    };
  }
}
