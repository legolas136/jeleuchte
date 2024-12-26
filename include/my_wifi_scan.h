#ifndef MY_WIFI_SCAN_H
#define MY_WIFI_SCAN_H

#include <Arduino.h>
#include <WiFi.h>
#include "my_wifi.h"

extern WiFiClass WiFi;

void wifi_scan_async();
void wifi_scan_blocking();
void wifi_scan_portal();

#endif