#ifndef MY_MDNS_H
#define MY_MDNS_H

#include <Arduino.h>
#include <ESPmDNS.h>
#include "my_wifi.h"

struct KnownVislinks
{
    uint8_t amount_of_vislinks_found;
    IPAddress ips[255];
    uint16_t ports[255];
    String descriptions[255];
};

void setupMdns(const char *_hostname= config.wifi_hostname, const char *_instanceName = "vislink");

void discover_vislink_service();

void addMdnsService(uint16_t _servicePort, const char *_serviceType, const char *_serviceDescription);

#endif