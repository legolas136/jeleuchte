#ifndef MY_RF24_H
#define MY_RF24_H

#include <Arduino.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24Network.h>

#include "my_parser.h"
#include "my_specials.h"
#include "globals.h"

// #define RF24_OLD_MODE

#define PIN_CE 17 // GPIO for ChipEnable
#define PIN_CSN 5 // GPIO for ChipSelectNot


/*

GND     GND
CE      17 (TX2)
SCK     18
MISO    19

VCC     3v3
CNS     5
MOSI    23
IRQ     

*/


#ifdef RF24_OLD_MODE
const byte rf24_writeAddress[6] = "007";    // Address of the master (for Ack-Payloads)
const byte rf24_readAddress[6] = "001";     // Address of the slave (this Controller)
const byte rf24_readAddressMisc[6] = "005"; // Additional adress of the slave (this Controller)

extern RF24 radio;

#else
struct payload_t
{ // Structure of our payload
    uint8_t band_values[NUMBER_OF_BANDS];
};

extern RF24Network network;
extern payload_t payload;
#endif

bool rf24_init();
void listenRF();

#endif