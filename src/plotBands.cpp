#include "plotBands.h"

void plotBands()
{
    static unsigned long lastmillis = millis();
    // if (millis() - lastmillis > 10)
    // {
        // plotbandsLevelAverage();
        plotReceived();
        // plotautoMapped();
        // plotHighestValues();

        // Serial.print("Bass");
        // Serial.print(":");
        // Serial.print(Bass.getOutput() + 10 * 255);
        // Serial.print(",");

        // Serial.print("Mid");
        // Serial.print(":");
        // Serial.print(Mid.getOutput() + 11 * 255);
        // Serial.print(",");

        // Serial.print("Treble");
        // Serial.print(":");
        // Serial.print(Treble.getOutput() + 12 * 255);

        Serial.println();

        lastmillis = millis();
    // }
}

void plotReceived()
{
    for (int i = 0; i < NUMBER_OF_BANDS; i++)
    {
        Serial.print("Band ");
        Serial.print(i);
        Serial.print("= ");
        //Serial.print(bands_level[i]);
        Serial.print(dsp.bandLevelsReceived[i] + (i * 200));
        Serial.print(", ");
    }
}

void plotautoMapped()
{
    for (int i = 0; i < NUMBER_OF_BANDS; i++)
    {
        Serial.print("Band ");
        Serial.print(i);
        Serial.print("= ");
        //Serial.print(bands_level[i]);
        Serial.print(dsp.bands_level_automapped[i] + (i * 200));
        Serial.print(", ");
    }
}

void plotCachedSum()
{
    for (int i = 0; i < NUMBER_OF_BANDS; i++)
    {
        Serial.print("xBand");
        Serial.print(i);
        Serial.print(":");
        Serial.print(dsp.bands_level_cached_sum[i] + (i * 255));
        // Serial.print(dsp.bandLevelsReceived[i] + i*255);
        Serial.print(",");
    }
}

void plotbandsLevelAverage()
{
    for (int i = 0; i < NUMBER_OF_BANDS; i++)
    {
        Serial.print("xBand");
        Serial.print(i);
        Serial.print(":");
        Serial.print(dsp.bandsLevelAverage[i] /*+ (i * 255)*/);
        // Serial.print(dsp.bandLevelsReceived[i] + i*255);
        Serial.print(",");
    }
}

void plotHighestValues()
{
    for (int i = 0; i < NUMBER_OF_BANDS; i++)
    {
        Serial.print("xBand");
        Serial.print(i);
        Serial.print(":");
        Serial.print(dsp.bands_highest_level[i] /*+ (i * 255)*/);
        // Serial.print(dsp.bandLevelsReceived[i] + i*255);
        Serial.print(",");
    }
}