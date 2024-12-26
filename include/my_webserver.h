#ifndef MY_WEBSERVER_H
#define MY_WEBSERVER_H

#define ASYNC_WEBSERVER_PORT 80
#define OTA_USER "ota"
#define OTA_PASSWORD "ota"
#include <AsyncElegantOTA.h>

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <WString.h>
#include "functionMappings.h"



// to be able to open files from spiffs
#include "my_spiffs.h"

// program-specific
// needed to find program-specific variables, classes, objects and functions
#include "my_wifi_scan.h"
#include "_class_dsp.h"
#include "globals.h"
#include "my_fastled_init.h"
#include "my_fastled_handle.h"
#include "my_rf24.h"
#include "my_preferences.h"
#include "my_remote_cmds.h"
#include "my_prefs_struct.h"
#include "my_update_http.h"
#include "my_pwm.h"
#include <version.h>
#include <version_spiffs.h>
#include <ArduinoJson.h>

extern RF24 radio;
extern MSGEQ7_DSP dsp;
extern String found_wifis[10];
extern MyPwm MyPwm1;
extern uint8_t led_alarm_active;
// extern uint16_t SPIFFSVersion;

// end programm specific



// Replaces placeholder in html file
extern String processor(const String &var);

// Sets up webserver & handling
void setupWebServer();
void initWebSocket();
void tickWebSockets();
void sendOverWebsockets(String message);
void handleUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);

// void handleUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);

#endif