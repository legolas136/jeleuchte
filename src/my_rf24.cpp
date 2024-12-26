#include "my_rf24.h"

RF24 radio(PIN_CE, PIN_CSN); // Configure pins for ChipEnable and ChipSelectNot

payload_t payload;
RF24Network network(radio);

bool rf24_init()
{
  // return value
  bool is_connected = false;

  Serial.print("Setting up nRF24L01 network. Address: ");
  Serial.println(config.rf24_node_address, 8);
  if(!radio.begin()) // create RF24 radio
  {
    return false;
  }
  is_connected = true;
  radio.setChannel(90);
  network.begin(/*node address*/ config.rf24_node_address);
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_MAX);

  return is_connected; //-------------------RF24end----------------------------------
}

void listenRF()
{ // listens for incoming data on nRF24L01 module in format:
  // i;v1,v2,v3,v4,v5,v6,v7 where i = identifier and v1-v7 = value of bands
  uint8_t pipeNumber;
  if (radio.available(&pipeNumber))
  { // if data has arrived
    // rf24_in_fps(2);
    new_data = true; // set "new_data to true", so the loop knows, that there is something to process

    char textBuffer[33] = {};                   // create a 32-byte buffer to hold incoming data
    radio.read(textBuffer, sizeof(textBuffer)); // read the arrived data into this buffer
    parsePayload(textBuffer); // parse the payload
  }
}

unsigned strToOct(const char *str, int base)
{
    const char digits[] = "01234567890ABCDEF";
    unsigned result = 0;

    while(*str)
    {
        result *= base;
        result += strchr(digits, *str++) - digits;
    }
    return result;
}