#ifndef DEFINITIONS_H
#define DEFINITIONS_H
// Eindeutige ID
// #define NODE_ADDRESS 01

// UART
#define BAUDRATE 500000

// WiFi
// #define IS_HOME
// #define WIFI_RECONNECT_INTERVALL 5000
// #define WIFI_STA_SSID "Alice-D"
// #define WIFI_STA_PASSWORD "Multiketaminsaft"
// #define WIFI_AP_SSID "ESP32-AP"

// mDNS
#define MY_MDNS_SERVICE_NAME "vislink"
// #define VISLINK_DESCRIPTION "kueche"

// MQTT
#define MQTT_SERVER_IP "192.168.1.209"
#define MQTT_SERVER_PORT 1883
#define MQTT_TOPIC "wz/esp32"
#define MQTT_RECONNECT_INTERVAL 5000
#define MQTT_USER "mqtt"
#define MQTT_PASSWORD "password"

// DSP
#define NUMBER_OF_BANDS 16

#endif