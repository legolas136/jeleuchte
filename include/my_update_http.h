#ifndef MY_HTTP_H
#define MY_HTTP_H

#include <HTTPClient.h>
#include <WiFiClient.h>
// #include <SPIFFS.h>
#include <Update.h>
#include "my_config.h"
#include "my_fastled_init.h"
#include "my_fastled_handle.h"

void visualizeDownload();

void download_fw();

void updateRun(const char* _host);

void updateRunSpiffs(const char* _host);

void updateProcess(uint8_t *data, size_t len);

#endif

