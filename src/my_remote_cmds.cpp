#include "my_remote_cmds.h"

void dimUp(uint8_t delta)
{
  if((255 - config.global_brightness) >= delta)
  {
    config.global_brightness = config.global_brightness + delta;
  }
  else
  {
    config.global_brightness = 255;
  }
}

void dimDown(uint8_t delta)
{
  if(config.global_brightness >= delta)
  {
    config.global_brightness = config.global_brightness - delta;
  }
  else
  {
    config.global_brightness = 0;
  }
}

void programIncrease()
{
  if(config.program <= 12)
  {
    config.program++;
  }
}

void programDecrease()
{
  if(config.program >= 2)
  {
    config.program--;
  }
}
