#ifndef MY_SPIFFS_H
#define MY_SPIFFS_H

#include <SPIFFS.h>

#include "my_config.h"
extern my_preferences config;


void setupSpiffs();

bool configIniCheckExistence();
int getSPIFFSVersion();
void configIniManagement();
void configIniCreateNew();
void configIniRead(const char* configfile = "/config.ini");
void configIniWriteWifiConfig();
void configIniWriteProgramConfig();
void configIniParseLine(const char *str);
void configIniSetData (String key, String value);
void configIniDelete();
void printCurrentConfig();

#endif