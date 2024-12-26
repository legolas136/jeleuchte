#ifndef _CLASS_DSP_H
#define _CLASS_DSP_H

#include <Arduino.h>

#include "definitions.h"
// #include "globals.h"
#include "_class_DampenedVal.h"

#define READINGS_PER_SECOND 200

class MSGEQ7_DSP
{
private:
public:
    uint16_t bandLevelsReceived[NUMBER_OF_BANDS]; // Array to hold the values for each band received from master

    uint16_t bands_level_cached_sum[NUMBER_OF_BANDS];
    uint16_t bands_level_automapped[NUMBER_OF_BANDS];
    uint16_t bands_highest_level[NUMBER_OF_BANDS];
    uint16_t bands_level_out[NUMBER_OF_BANDS];
    int bands_multi[NUMBER_OF_BANDS] = {127, 127, 127, 127, 127, 127, 127};
    float bands_level_zoom_factor = 1;
    int bands_level_offset = 0;
    uint16_t brModeFallingSpeed = 2200;
    uint16_t bassFallingSpeed = 800;
    uint16_t midFallingSpeed = 600;
    uint16_t trebleFallingSpeed = 400;
    bool brModeOn = 0;
    bool brModePwmOn = 0;
    uint32_t overallVolume = 1;
    uint32_t overallVolumeAverage = 1;
    uint32_t bandsLevelAverageBucket[NUMBER_OF_BANDS][READINGS_PER_SECOND]; // 2-dimensional array to hold the last n readings of each band
    uint32_t bandsLevelAverage[NUMBER_OF_BANDS];                            // Array to hold the calculated average values of each band
    uint16_t avr_array_index = 0;                                           // Helper to store the position within the array >xxx<??????
    float bands_pitch[NUMBER_OF_BANDS];                                     // Array to store the calculated rise/fall of the bands

    

    void filterLevels(uint16_t (&input)[NUMBER_OF_BANDS], uint16_t threshold);

    uint16_t calcOverallVolume(uint16_t (&input)[NUMBER_OF_BANDS]);

    uint16_t calcOverallVolumeAverage();

    void calculateLevelAverages();

    void calcPitch();

    void bands_level_multiplier();

    void bands_level_manipulate(float factor, int offset);

    uint16_t returnHighestBandLevel(uint8_t fromLevel, uint8_t toLevel);

    void trackHighestLevel(uint16_t ReductionInterval = 200);

    void autoMap(uint16_t desiredMax = 225);

    void signalProcessing();

};

extern MSGEQ7_DSP dsp;

#endif