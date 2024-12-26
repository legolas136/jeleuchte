#ifndef MY_WIFI_H
#define MY_WIFI_H
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "my_config.h"
extern my_preferences config;

int setupAP(const char* ssid = config.wifi_AP_ssid);
void setupWifi(const char* ssid = config.wifi_ssid, const char* pw = config.wifi_password, const char* hostname = config.wifi_hostname);
// void setupWifi(const char* ssid, const char* pw, const char* hostname);
void wifiReconnect(uint32_t intervall = 5000);
void my_ota_onstart_routine();
void setupOTA();
void OTA_tick();

#endif