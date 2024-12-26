#ifndef MY_MQTT_H
#define MY_MQTT_H

#include <Arduino.h>
#include <PubSubClient.h>

#include "my_fastled_init.h"
#include "my_wifi.h"
#include "my_specials.h"
#include "definitions.h"
#include "my_wifi.h"
#include "globals.h"
#include "my_dampenedval_objects.h"


struct MqttConfig
// Struct to hold config. Types 'byte' und 'word' don't work!
{
    IPAddress server_ip;
    char server_ip_as_char[14];
    uint16_t server_port;
    char server_port_as_char[6];
    char id[17];
    char user[33];
    char password[33];
    char room[33];
};

extern MqttConfig mqttConfig;
// extern PubSubClient mqttclient;


// #include 
// #include "fastled_functions.h"

// extern IPAddress mqttServer(192, 168, 1, 112);

// WiFiClient espClient;

// extern PubSubClient mqttclient(espClient);

void mqtt_subsriptions();
void mqttcallback(char *topic, byte *payload, unsigned int length);
void setupMqtt();
void mqtt_reconnect(uint16_t mqtt_reconnect_intervall = MQTT_RECONNECT_INTERVAL);
void mqtttest();
void send_mqtt_data(unsigned long interval = 1000);
void mqttPublish(const char *topic, const char *msg);
void mqttTick();
String mqtt_built_topic(const char *trailing_topic = "#", bool is_room = false);

#endif