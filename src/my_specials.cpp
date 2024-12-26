#include "my_specials.h"

unsigned long global_fps;

void fps(const int seconds)
{
    static unsigned long lastMillis;
    static unsigned long lastMillisPrint;
    static unsigned long frameCount;
    static unsigned int framesPerSecond;
    unsigned long now_fps = millis(); // It is best if we declare millis() only once

    frameCount++;
    if (now_fps - lastMillis >= seconds * 1000)
    {
        framesPerSecond = frameCount / seconds;
        global_fps = framesPerSecond;
        frameCount = 0;
        lastMillis = now_fps;
    }
    if (now_fps - lastMillisPrint >= 500)
    {
        lastMillisPrint = now_fps;
        last_fps = framesPerSecond;
        // Serial.println(framesPerSecond);
    }
}

void rf24_in_fps(const int seconds)
{
    static unsigned long lastMillis;
    static unsigned long lastMillisPrint;
    static unsigned long frameCount;
    static unsigned int framesPerSecond;
    unsigned long now_fps = millis(); // It is best if we declare millis() only once

    frameCount++;
    if (now_fps - lastMillis >= seconds * 1000)
    {
        framesPerSecond = frameCount / seconds;
        frameCount = 0;
        lastMillis = now_fps;
    }
    if (now_fps - lastMillisPrint >= 500)
    {
        lastMillisPrint = now_fps;
        last_rf24_fps = framesPerSecond;
        Serial.print("Rcvd RF24 per second: ");
        Serial.println(framesPerSecond);
    }
}

void getFreeHeap()
{
    Serial.println(ESP.getFreeHeap());
}

String getChipID()
{
    String chipId = String((uint32_t)ESP.getEfuseMac(), HEX);
    chipId.toUpperCase();
    #ifdef SERIAL_DEBUG
    Serial.printf("Chip id: %s\n", chipId.c_str());
    #endif
    return chipId;
}

void printChipID()
{
    String chipId = String((uint32_t)ESP.getEfuseMac(), HEX);
    chipId.toUpperCase();

    Serial.printf("Chip id: %s\n", chipId.c_str());
}

void checkChipID()
{
    // String((uint32_t)ESP.getEfuseMac(), HEX) found in asyncelegantota lib
    uint64_t chipid = ESP.getEfuseMac();
    Serial.println((uint16_t)(chipid >> 32));
    Serial.println((uint32_t)chipid);
    Serial.println();
    Serial.printf("ESP32 Chip ID = %04X", (uint16_t)(chipid >> 32)); //print High 2 bytes
    Serial.printf("%08X\n", (uint32_t)chipid);                       //print Low 4bytes.
    if ((uint16_t)(chipid >> 32) == 52282 && (uint32_t)chipid == 4188758564)
    {
        Serial.println("Chip recognised");
    }
    else
    {
        Serial.println("Fuck you!");
        //while(true);
    }
}

void handle_error()
{
    
}
