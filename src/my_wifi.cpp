#include "my_wifi.h"


// WiFiConfig wifiConfig;

// bool wifi_auto_reconnect = false;

int setupAP(const char *ssid)
{
    Serial.print("Setting up AP with SSID: ");
    Serial.println(ssid);

    if (WiFi.softAP(ssid))
    {
        Serial.print("AP IP: ");
        Serial.println(WiFi.softAPIP());
        return 1;
    }
    else
    {
        return -1;
    }
}

void setupWifi(const char* ssid, const char* pw, const char* hostname)
{
    Serial.print("Setting up Wifi on ");
    Serial.print(ssid);
    // Serial.print(" with pw: ");
    // Serial.print(pw);
    Serial.print(". Hostname is  ");
    WiFi.setHostname(hostname);
    Serial.print(": ");
    

    WiFi.mode(WIFI_AP_STA);

    if (strcmp(ssid, "unconfigured") != 0)
    {
        Serial.print("connecting to station... ");
        WiFi.begin(ssid, pw);

        if (WiFi.waitForConnectResult() == WL_CONNECTED)
        {
            Serial.println("success!");
            Serial.print("STA IP: ");
            Serial.println(WiFi.localIP());
            WiFi.enableAP(false);
            Serial.println("Closing AP");
            config.wifi_auto_reconnect = true;
            Serial.println("Enabled automatic reconnect");
            Serial.println("--------------------");
        }
        else
        {
            Serial.println("failed!");
        }
    } else{
        Serial.println("WiFi not configured!");
    }
}

void wifiReconnect(uint32_t intervall)
{
    if (WiFi.status() != WL_CONNECTED && (config.wifi_auto_reconnect == true))
    {
        static uint32_t lastmillis = millis();
        static bool report_disconnected = false;
        if (!report_disconnected)
        {
            Serial.println("Wifi disconnected, starting Access Point");
            setupAP(config.wifi_AP_ssid);
            Serial.println("Scanning and trying to reconnect every 5 seconds");
            report_disconnected = true;
        }
        if (millis() - lastmillis >= intervall)
        {
            WiFi.reconnect();
            Serial.println("Starting wifi_scan_async...");
            lastmillis = millis();

            //delayMicroseconds(10);
            //WiFi.mode(WIFI_STA);
            //wifi_scan_blocking();
            // wifi_scan_async();
        }
    }
}

void my_ota_onstart_routine()
{
    // power_switch = false;
}

void setupOTA()
{
    Serial.print("Setup OTA: ");
    // ArduinoOTA.setHostname("ESP32_test");
    //    ArduinoOTA.setPassword("admin");

    ArduinoOTA
        .onStart([]() {
            my_ota_onstart_routine();
            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
            else // U_SPIFFS
                type = "filesystem";

            // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
            Serial.println("Start updating " + type);
        })
        .onEnd([]() {
            Serial.println("\nEnd");
            ESP.restart();
        })
        .onProgress([](unsigned int progress, unsigned int total) {
            Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
        })
        .onError([](ota_error_t error) {
            Serial.printf("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR)
                Serial.println("Auth Failed");
            else if (error == OTA_BEGIN_ERROR)
                Serial.println("Begin Failed");
            else if (error == OTA_CONNECT_ERROR)
                Serial.println("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR)
                Serial.println("Receive Failed");
            else if (error == OTA_END_ERROR)
                Serial.println("End Failed");
        });
    ArduinoOTA.begin();
    Serial.println("ready!");
}

void OTA_tick()
{
    ArduinoOTA.handle();
}