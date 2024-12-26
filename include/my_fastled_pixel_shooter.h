#ifndef MY_FASTLED_PIXEL_SHOOTER_H
#define MY_FASTLED_PIXEL_SHOOTER_H

#include <Arduino.h>

struct my_fastled_pixel_shooter
{
    uint8_t center;
};


class ShootingPixel
{
private:
public:
uint16_t pixel_mid_address;
uint8_t pixel_dimension;
uint8_t pixel_speed;
unsigned long pixel_ttl;

};


#endif