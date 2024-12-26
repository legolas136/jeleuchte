#include "my_update_http.h"

extern my_preferences config;

int totalLength;       // total size of firmware
int currentLength = 0; // current size of written firmware

void visualizeDownload()
{
    int _percentage = (currentLength * 100) / totalLength;
    int _pixels_done = (config.num_leds_connected * _percentage)  / 100 ;
    // Serial.print("Percentage done:");
    // Serial.println(_percentage);
    // Serial.print("Mapped to pixels:");
    // Serial.println(_pixels_done);

    for (int i = 0; i < _pixels_done; i++)
    {
        leds[i].r = uint8_t(255 - _percentage);
        leds[i].g = uint8_t(_percentage);
        leds[i].b = uint8_t(127 - _percentage);
    }

    static unsigned long lastmillis = millis();
    if (millis() - lastmillis >= 500)
    {
        lastmillis = millis();
        FastLED.show();
    }
}

void updateRun(const char *_host)
{
    power_switch = false;
    blanken();
    Serial.print("Disabling WDTs: ");
    disableCore0WDT();
    disableCore1WDT();
    delay(1000);
    Serial.println("success!");

    HTTPClient client;
    client.begin(_host);
    // Get file, just to check if each reachable
    int resp = client.GET();
    Serial.print("Response: ");
    Serial.println(resp);
    // If file is reachable, start downloading
    if (resp == 200)
    {
        // get length of document (is -1 when Server sends no Content-Length header)
        totalLength = client.getSize();
        // transfer to local variable
        int len = totalLength;
        // this is required to start firmware update process
        Update.begin(UPDATE_SIZE_UNKNOWN);
        Serial.printf("FW Size: %u\n", totalLength);
        // create buffer for read
        uint8_t buff[128] = {0};
        // get tcp stream
        WiFiClient *stream = client.getStreamPtr();
        // read all data from server
        Serial.println("Updating firmware...");
        while (client.connected() && (len > 0 || len == -1))
        {
            // get available data size
            size_t size = stream->available();
            if (size)
            {
                // read up to 128 byte
                int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
                // pass to function
                updateProcess(buff, c);
                if (len > 0)
                {
                    len -= c;
                }
            }
            delayMicroseconds(25);
        }
    }
    else
    {
        Serial.println("Cannot download firmware file. Only HTTP response 200: OK is supported. Double check firmware location #defined in HOST.");
    }
    client.end();
}

void updateRunSpiffs(const char *_host)
{
    power_switch = false;
    Serial.print("Disabling WDTs: ");
    disableCore0WDT();
    disableCore1WDT();
    delay(1000);
    Serial.println("success!");

    HTTPClient client;
    client.begin(_host);
    // Get file, just to check if each reachable
    int resp = client.GET();
    Serial.print("Response: ");
    Serial.println(resp);
    // If file is reachable, start downloading
    if (resp == 200)
    {
        // get length of document (is -1 when Server sends no Content-Length header)
        totalLength = client.getSize();
        // transfer to local variable
        int len = totalLength;
        // this is required to start firmware update process
        Update.begin(UPDATE_SIZE_UNKNOWN, U_SPIFFS);
        Serial.printf("SPIFFS Size: %u\n", totalLength);
        // create buffer for read
        uint8_t buff[128] = {0};
        // get tcp stream
        WiFiClient *stream = client.getStreamPtr();
        // read all data from server
        Serial.println("Updating SPIFFS...");
        while (client.connected() && (len > 0 || len == -1))
        {
            // get available data size
            size_t size = stream->available();
            if (size)
            {
                // read up to 128 byte
                int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
                // pass to function
                updateProcess(buff, c);
                if (len > 0)
                {
                    len -= c;
                }
            }
            delayMicroseconds(25);
        }
    }
    else
    {
        Serial.println("Cannot download SPIFFS file. Only HTTP response 200: OK is supported. Double check SPIFFS location.");
    }
    client.end();
}

// Function to update firmware incrementally
// Buffer is declared to be 128 so chunks of 128 bytes
// from firmware is written to device until server closes
void updateProcess(uint8_t *data, size_t len)
{
    
    vTaskDelay(1);
    Update.write(data, len);
    currentLength += len;
    visualizeDownload();
    // Print dots while waiting for update to finish
    // Serial.print('.');
    // if current length of written firmware is not equal to total firmware size, repeat
    if (currentLength != totalLength)
        return;
    Update.end(true);
    for (int i = 0; i < config.num_leds_connected; i++)
    {
        leds[i].r = uint8_t(0);
        leds[i].g = uint8_t(255);
        leds[i].b = uint8_t(255);
    }
    blanken();
    Serial.printf("\nUpdate Success, Total Size: %u\nRebooting...\n", currentLength);
    // Restart ESP32 to see changes
    ESP.restart();
}