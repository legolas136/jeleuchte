#include "_class_dsp.h"

MSGEQ7_DSP dsp;

void MSGEQ7_DSP::filterLevels(uint16_t (&input)[NUMBER_OF_BANDS], uint16_t threshold)
{
  for (int i = 0; i < NUMBER_OF_BANDS; i++)
  { // Now sum up all 7 bands
    if (input[i] < threshold)
    {
      input[i] = 0;
    }
  }
}

uint16_t MSGEQ7_DSP::calcOverallVolume(uint16_t (&input)[NUMBER_OF_BANDS])
{
  // Function to calc the current overall energy (="volume")
  overallVolume = 0; // Reset the sum of all bands
  for (int i = 0; i < NUMBER_OF_BANDS; i++)
  { // Now sum up all bands
    overallVolume += input[i];
  }
  overallVolume = overallVolume / NUMBER_OF_BANDS;  // Divide by number of bands to get back to 1-byte-range
  overallVolume = constrain(overallVolume, 0, 255); // Constrain to max value 255
  return overallVolume;
}

void MSGEQ7_DSP::calculateLevelAverages()
{
  // Put new values into current row (avr_array_index) of 2-dimensional array
  for (int i = 0; i < NUMBER_OF_BANDS; i++)
  {                                                                      // All bands...
    bandsLevelAverage[i] = 0;                                            // Reset the last average value
    bandsLevelAverageBucket[i][avr_array_index] = bandLevelsReceived[i]; // Throw current band-values into the bucket
  }

  // Calculate the new averages
  for (int i = 0; i < NUMBER_OF_BANDS; i++)
  { // All bands...
    for (int j = 0; j < READINGS_PER_SECOND - 1; j++)
    {                                                        // Sum up all values within the bucket
      bandsLevelAverage[i] += bandsLevelAverageBucket[i][j]; // i: band, j:index position of the bucket
    }
    bandsLevelAverage[i] = bandsLevelAverage[i] / READINGS_PER_SECOND; // Divide by READINGS_PER_SECOND to get back to 1-byte-range (0-255)
  }

  // Preparation for next execution
  avr_array_index++; // Set to next row of 2 dimensional array
  if (avr_array_index >= READINGS_PER_SECOND - 1)
    avr_array_index = 0; // Reset avr_array_index to 0 to create an infinity loop
}

void MSGEQ7_DSP::calcPitch()
{
  for (int i = 0; i < NUMBER_OF_BANDS; i++)
  { // All bands...
    if (bandsLevelAverage[i] == 0)
    {                                                                          // If avergage == 0...
      bands_pitch[i] = (bandLevelsReceived[i] / (bandsLevelAverage[i] + 0.1)); // Pitch = Level/(Average +0.1) (Prevent division by 0)
    }
    else
    {
      bands_pitch[i] = (bandLevelsReceived[i] / (float(bandsLevelAverage[i]))); // Pitch = Level/Average
    }
    if (bands_pitch[i] < 0)
      bands_pitch[i] = 0; // Only take care of positive pitch
  }
}

void MSGEQ7_DSP::bands_level_multiplier()
{
  // Manipulate the values of bands (zero to double)
  for (int i = 0; i < NUMBER_OF_BANDS; i++)
  {                                                                                             // All bands...
    this->bandLevelsReceived[i] = this->bandLevelsReceived[i] * this->bands_multi[i] * 2 / 255; // Multiply with multiplier and '2' to amplify, if value is low
    if (this->bandLevelsReceived[i] > 255)
      this->bandLevelsReceived[i] = 255; // Constrain to max value 255
  }
}

void MSGEQ7_DSP::bands_level_manipulate(float factor, int offset)
{
  for (int i = 0; i < NUMBER_OF_BANDS; i++)
  {                                                                     // All bands...
    this->bandLevelsReceived[i] = this->bandLevelsReceived[i] * factor; // Multiply with multiplier and '2' to amplify, if value is low
    if (this->bandLevelsReceived[i] + offset >= 0)
      this->bandLevelsReceived[i] += offset;
    if (this->bandLevelsReceived[i] > 255)
      this->bandLevelsReceived[i] = 255; // Constrain to max value 255
  }
}

uint16_t MSGEQ7_DSP::returnHighestBandLevel(uint8_t fromLevel, uint8_t toLevel)
{
  uint8_t highest_level = 0;
  for (int i = fromLevel; i < toLevel; i++)
  {
    if (highest_level < this->bandLevelsReceived[i])
      highest_level = this->bandLevelsReceived[i];
  }
  return highest_level;
}

uint16_t MSGEQ7_DSP::calcOverallVolumeAverage()
{
  this->overallVolumeAverage = 0;

  for (int i = 0; i < NUMBER_OF_BANDS; i++)
  {
    this->overallVolumeAverage += this->overallVolume;
  }

  this->overallVolumeAverage = this->overallVolumeAverage / NUMBER_OF_BANDS;

  if (this->overallVolumeAverage > 255)
  {
    this->overallVolumeAverage = 255;
  }
  if (this->overallVolumeAverage <= 0)
  {
    this->overallVolumeAverage = 1;
  }
  return this->overallVolumeAverage;
}

void MSGEQ7_DSP::trackHighestLevel(uint16_t ReductionInterval)
{
  static unsigned long lastmillis = millis();

  for (int i = 0; i < NUMBER_OF_BANDS; i++)
  {
    if (bandLevelsReceived[i] > bands_highest_level[i])
    {
      bands_highest_level[i] = bandLevelsReceived[i];
    }
    else
    {
      if (millis() - lastmillis > ReductionInterval)
      {
        for (int i = 0; i < NUMBER_OF_BANDS; i++)
        {
          if(bands_highest_level[i] > 35)
          bands_highest_level[i]--;
        }
        lastmillis = millis();
      }
    }
  }
}

// Function to raise band values, which are too silent
void MSGEQ7_DSP::autoMap(uint16_t desiredMax)
{
  // Do it on every Band
  for (int i = 0; i < NUMBER_OF_BANDS; i++)
  {
    // bands_level_automapped[i] = map(bandLevelsReceived[i], 0, bands_highest_level[i], 0, 255);
    bands_level_automapped[i] = map(bandLevelsReceived[i], 0, bands_highest_level[i], 0, 255);
    // bands_level_automapped[i] = map(bandLevelsReceived[i], 0, bands_highest_level[i], 0, 255);
    bands_level_automapped[i] = constrain(bands_level_automapped[i], 0, 255);
  }
}

void MSGEQ7_DSP::signalProcessing()
{

  // this->filterLevels(bands_level_cached_sum, 13);
  // trackHighestLevel();
  // autoMap();
  // calcOverallVolume(bandLevelsReceived); // First calculate the energy over all frequency bands -> ="overall volume"
  // calcOverallVolumeAverage();
  calculateLevelAverages();
  // calcPitch();
  // this->bands_level_multiplier(); // Multiply with factors to manipulate the impact of certain freq ranges on effects
  this->bands_level_manipulate(bands_level_zoom_factor, bands_level_offset);
}
