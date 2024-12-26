// #define USE_PREFERENCES
// #define USE_CONFIG_INI
#include <version.h>
#include <Arduino.h>

#include "my_preferences.h"
#include "definitions.h"
#include "_class_dsp.h"

#include "my_wifi.h"
#include "my_specials.h"
#include "my_mqtt.h"
#include "my_fastled_init.h"
#include "my_fastled_handle.h"
#include "my_webserver.h"
#include "my_dampenedval_objects.h"
#include "my_prefs_struct.h"
#include "my_mdns.h"
#include "my_pwm.h"

bool update_needed = false;
bool spiffs_update_needed = false;
uint16_t SPIFFSVersion = 1;

MyPwm MyPwm1;

extern DampenedBands dampenedBands;
extern MSGEQ7_DSP dsp;

void setup()
{
    Serial.begin(BAUDRATE);
    Serial.println("Programm started...");
    setupSpiffs();

    // ____________________________________________________________________________________
    // reading configurations

    // printCurrentConfig();
    Serial.println("_________________READING CONFIG_______________________");
    // prefsLoadProgram(); // ambiguous. will be removed if prefs_struct_... is safe!
    prefs_struct_read();
    configIniRead("/wifi.ini");
    // prefsLoadNetwork();
    // printCurrentConfig();

    // ____________________________________________________________________________________
    // setting up wifi
    setupAP(config.wifi_AP_ssid);
    setupWifi(config.wifi_ssid, config.wifi_password, config.wifi_hostname);
    setupOTA();

    // ____________________________________________________________________________________
    // other modules
    setupMqtt();
    fastled_init();
    setupWebServer();
    initWebSocket();
    setupMdns();
    // discover_vislink_service();

    if (!rf24_init())
    {
        handle_error();
    }

    MyPwm1.setup();
    MyPwm1.setBrightnessPercent(5);

    // for (int i = 0; i < NUMBER_OF_BANDS; i++)
    // {
    //     Serial.print(dampenedBands.getOutput(i));
    //     Serial.println();
    // }
}

void loop()
{
    updateDampenedValues();
    // dampenedBands.printOutput(20);
    // fps();

    OTA_tick(); //
    wifiReconnect(5000);
    if (update_needed)
    {
        updateRun(config.fw_update_server);
    }
    if (spiffs_update_needed)
    {
        updateRunSpiffs(config.spiffs_update_server);
    }
    // mqttTick();
    fps();
    tickWebSockets();

    if (radio.isChipConnected())
    // If the nRF24L01 is connected ...
    {
        // Listen for data on radio

        network.update(); // Check the network regularly
        while (network.available())
        { // Is there anything ready for us?

            RF24NetworkHeader header; // If so, grab it and print it out
            network.read(header, &payload, sizeof(payload));

            for (int i = 0; i < NUMBER_OF_BANDS; i++)
            {
                dsp.bandLevelsReceived[i] = payload.band_values[i];
            }
            
        }
        // dsp.signalProcessing(); // DSP: Manipulate the data arrived: multiply with factors, calc averages, etc.
    }
    // plotBands();
    if (power_switch == true) // software main-switch
    {
        ledHandle(45); // All LED related stuff (program, output, etc.)
    }
}