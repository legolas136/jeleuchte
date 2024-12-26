#ifndef MY_PREFERENCES_H
#define MY_PREFERENCES_H

#include <Preferences.h>

#include "my_config.h"
#include "my_specials.h"
#include "my_spiffs.h"
extern my_preferences config;


// extern Preferences prefs;


void prefsInitNetwork();
void prefsWriteCurrentWifiConfig();
void prefsWriteCurrentProgramConfig();
void prefsInitProgram();
bool prefsLoadNetwork();
bool prefsLoadProgram();
void printConfig();
void prefsClearWifi();
void prefsClearProgram();

#endif