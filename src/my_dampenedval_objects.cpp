#include "my_dampenedval_objects.h"

DampenedVal OverallVolume;
DampenedVal Bass;
DampenedVal Mid;
DampenedVal Treble;
DampenedVal BrMode;
DampenedBands dampenedBands;

void updateDampenedValues()
{

#if NUMBER_OF_BANDS == 7
    // DampenedVal::now = millis();
    OverallVolume.input = (dsp.overallVolume);
    // Bass.input = (dsp.bandLevelsReceived[0]);
    Bass.input = (((dsp.bandLevelsReceived[0] + dsp.bandLevelsReceived[0]) / 2) + dsp.bandLevelsReceived[1]) / 2;
    // Mid.input = dsp.returnHighestBandLevel(1, 5);
    Mid.input = dsp.returnHighestBandLevel(2, 4);
    Treble.input = (dsp.bandLevelsReceived[5] / 2) + (dsp.bandLevelsReceived[6] / 2);
    BrMode.input = (((dsp.bandLevelsReceived[0] + dsp.bandLevelsReceived[0]) / 2) + dsp.bandLevelsReceived[1]) / 2;

#endif

#if NUMBER_OF_BANDS == 16

    OverallVolume.input = (dsp.overallVolume);
    switch (config.accumulation_mode_bass)
    {
    case 0:
        Bass.input = dsp.returnHighestBandLevel(0, 2);

        break;
    case 1:
        Bass.input = (dsp.bandLevelsReceived[0]);
        break;
    case 2:
        Bass.input = constrain((dampenedBands.getOutput(0) + dampenedBands.getOutput(1) + dampenedBands.getOutput(2) + dampenedBands.getOutput(3) + dampenedBands.getOutput(4) + dampenedBands.getOutput(5)) / 3, 0, 255);
        break;

    default:
        break;
    }
    switch (config.accumulation_mode_mid)
    {
    case 0:
        Mid.input = dsp.returnHighestBandLevel(3, 11);
        break;
    case 1:
        Mid.input = dsp.returnHighestBandLevel(1, 5);
        break;
    case 2:
        Mid.input = dsp.returnHighestBandLevel(4, 7);
        break;

    default:
        break;
    }
    switch (config.accumulation_mode_treble)
    {
    case 0:
        Treble.input = dsp.returnHighestBandLevel(12, 15);
        break;
    case 1:
        Treble.input = dsp.returnHighestBandLevel(6, 15);
        break;
    case 2:
        Treble.input = dsp.returnHighestBandLevel(8, 15);
        break;

    default:
        break;
    }
    switch (config.accumulation_mode_br_mode)
    {
    case 0:
        Bass.input = (dsp.bandLevelsReceived[0]);
        break;
    case 1:
        Bass.input = (dsp.bandLevelsReceived[0]);
        break;
    case 2:
        Bass.input = (dsp.bandLevelsReceived[0]);
        break;

    default:
        break;
    }

    BrMode.input = dsp.returnHighestBandLevel(0, 1);
    // BrMode.input = (dsp.bandLevelsReceived[0] + dsp.bandLevelsReceived[1] + dsp.bandLevelsReceived[2]) / 3;

#endif

    OverallVolume.tick();
    dampenedBands.tick();
    // Bass.tick();
    // Mid.tick();
    // Treble.tick();
    Bass.tickMicroSeconds(dsp.bassFallingSpeed);
    Mid.tickMicroSeconds(dsp.midFallingSpeed);
    Treble.tickMicroSeconds(dsp.trebleFallingSpeed);
    BrMode.tickMicroSeconds(dsp.brModeFallingSpeed);
}