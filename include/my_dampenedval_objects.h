#include <Arduino.h>
#include "_class_DampenedVal.h"
#include "_class_dsp.h"
#include "plotBands.h"
#include "my_rf24.h"
#include "my_config.h"

extern DampenedVal OverallVolume;
extern DampenedVal Bands0;
extern DampenedVal Bands5;
extern DampenedVal Bass;
extern DampenedVal Mid;
extern DampenedVal Treble;

void updateDampenedValues();