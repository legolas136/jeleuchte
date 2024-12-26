#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

struct my_preferences
{
    bool autosave_enabled;
    char wifi_ssid[33];
    char wifi_password[64];
    char wifi_AP_ssid[33];
    char wifi_AP_password[64];
    char wifi_hostname[64];
    char fw_update_server[256] = "https://fw.linyo.de/firmware.bin";
    char spiffs_update_server[256] = "https://fw.linyo.de/spiffs.bin";
    bool wifi_auto_reconnect;
    uint16_t rf24_node_address = 2;

    int program = 6; //
    uint8_t global_brightness = 255;
    float pwm_brightness = 0;
    uint8_t fixed_color_r = 255;
    uint8_t fixed_color_g = 46;
    uint8_t fixed_color_b = 0;

    uint32_t deltamillis; //
    int brightness;       //
    int bands_multi[7];   //
    uint16_t num_leds_connected = 60;

    uint8_t gradient_color_1_h;
    uint8_t gradient_color_1_s;
    uint8_t gradient_color_1_v;

    uint8_t gradient_color_2_h;
    uint8_t gradient_color_2_s;
    uint8_t gradient_color_2_v;

    uint8_t hue_bass = 0;
    uint8_t hue_mid = 39;
    uint8_t hue_treble = 161;

    uint8_t led_color_order = 0;

    uint8_t accumulation_mode_bass = 0;
    uint8_t accumulation_mode_mid = 0;
    uint8_t accumulation_mode_treble = 0;
    uint8_t accumulation_mode_br_mode = 0;

    bool led_bed_mode = false;
};

#endif

/*
wifi_ssid =
wifi_password =
wifi_AP_ssid =
wifi_AP_password =
wifi_hostname =
rf24_node_address =
program =
global_brightness =
fixed_color_r =
fixed_color_g =
fixed_color_b =
deltamillis =
brightness =
num_leds_connected =
*/