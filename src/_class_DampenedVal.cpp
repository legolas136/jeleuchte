#include "_class_DampenedVal.h"

// uint16_t DampenedVal::cacheTime = 50;
// unsigned long DampenedVal::lastmillis = 0;
// unsigned long DampenedVal::now = 0;

extern MSGEQ7_DSP dsp;

uint8_t DampenedVal::getInput()
{
  return (this->input);
}

uint8_t DampenedVal::getOutput()
{
  return uint8_t(this->output);
}

void DampenedVal::setReductor(float input)
{
  this->reductor = input;
}

void DampenedVal::setIncrementor(float input)
{
  this->incrementor = input;
}

void DampenedVal::tick(uint8_t time_base)
{

  // calc delta. will be positive, if new value is bigger
  int delta = input - output;

  // if new val is bigger, immediately update
  if (delta > 0)
  {
    this->output = this->input;
  }

  // if new val is smaller
  else if (delta <= 0)
  {
    if (millis() - lastmillisTick >= time_base)
    {
      this->output = float(this->output) * float((this->reductor));
      lastmillisTick = millis();
    }
    // output = uint8_t(output) - 1;
  }

} // timing

void DampenedVal::tickMicroSeconds(uint16_t time_base)
{

  // calc delta. will be positive, if new value is bigger
  int delta = input - output;

  // if new val is bigger, immediately update
  if (delta > 0)
  {
    // // direct behaviour
    this->output = this->input;

    // smooth behaviour
    // output = (output + input) / 2;
  }

  // if new val is smaller
  else if (delta <= 0)
  {
    if (micros() - lastmicrosTick >= time_base)
    {
      this->output = float(this->output) * float((this->reductor));
      lastmicrosTick = micros();
    }
    // output = uint8_t(output) - 1;
  }

} // timing

// void DampenedVal::tickMicroSecondsNew(uint16_t time_base)
// {
//   // calc delta. will be positive, if new value is bigger
//   int delta = input - output;
//   // if new val is bigger, immediately update
//   if (delta > 0)
//   {
//     this->output = this->input;
//   }
//   // if new val is smaller
//   else if (delta <= 0)
//   {
//     if (micros() - lastmicrosTick >= time_base)
//     {
//       this->output = float(this->output) * float((this->reductor));
//       lastmicrosTick = micros();
//     }
//     // output = uint8_t(output) - 1;
//   }
// } // timing

////////////////////////////////////////////////////////
// DampenedBands

// uint8_t DampenedBands::getInput()
// {
//   return (this->input);
// }

uint8_t DampenedBands::getOutput(uint8_t band)
{
  return uint8_t(this->output[band]);
}

// void DampenedBands::setReductor(float input)
// {
//   this->reductor = input;
// }

// void DampenedBands::setIncrementor(float input)
// {
//   this->incrementor = input;
// }

// void DampenedBands::tick(uint8_t time_base)
// {

//   // calc delta. will be positive, if new value is bigger
//   int delta = input - output;

//   // if new val is bigger, immediately update
//   if (delta > 0)
//   {
//     this->output = this->input;
//   }

//   // if new val is smaller
//   else if (delta <= 0)
//   {
//     if (millis() - lastmillisTick >= time_base)
//     {
//       this->output = float(this->output) * float((this->reductor));
//       lastmillisTick = millis();
//     }
//     // output = uint8_t(output) - 1;
//   }

// } // timing

void DampenedBands::setFalligSpeed(uint8_t band, uint16_t falling_speed)
{
}

void DampenedBands::tick()
{
  int delta[NUMBER_OF_BANDS];
  // calc delta. will be positive, if new value is bigger
  for (int i = 0; i < NUMBER_OF_BANDS; i++)
  {
    delta[i] = dsp.bandLevelsReceived[i] - output[i];
  }

  // if new val is bigger, immediately update
  for (int i = 0; i < NUMBER_OF_BANDS; i++)
  {
    if (delta[i] >= 0)
    {
      // // direct behaviour
      output[i] = dsp.bandLevelsReceived[i];

      // smooth behaviour
      // output = (output + input) / 2;
    }

    // if new val is smaller
    else if (delta[i] < 0)
    {
      if (micros() - lastmicrosTick[i] >= fallingspeed[i])
      {
        output[i] = float(output[i]) * float((reductor[i]));
        this->lastmicrosTick[i] = micros();
      }
      // output = uint8_t(output) - 1;
    }
  }

} // timing

void DampenedBands::printOutput(uint16_t deltamillis)
{
  static unsigned long lastmillis = millis();

  if (millis() - lastmillis >= deltamillis)
  {
    uint16_t x = 0;
    lastmillis = millis();
    for (int i = 0; i < NUMBER_OF_BANDS; i++)
    {
      Serial.print(getOutput(i) + (i * 255));
      // Serial.print(dsp.bandLevelsReceived[i]);
      Serial.print(",");
    }

    for (int i = 0; i < 5; i++)
    {
      x = x + getOutput(i);
    }
    Serial.print(x * 3 + 2500);
    Serial.print(",");
    Serial.print("5000");
    Serial.println();
  }
}