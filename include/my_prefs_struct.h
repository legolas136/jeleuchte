#ifndef MY_PREFS_STRUCT_H
#define MY_PREFS_STRUCT_H

#include <Arduino.h>
#include <Preferences.h>
#include "my_config.h"
#include "my_preferences.h"

bool prefs_struct_write(const char* _namespace = "config_struct", const char* _parameter = "cfg_struct", my_preferences _config = config);

bool prefs_struct_read(const char* _namespace = "config_struct", const char* _parameter = "cfg_struct", my_preferences (&_config) = config);

bool prefs_struct_clear(const char* _namespace = "config_struct", const char* _parameter = "cfg_struct");

bool autosave_ifenabled();

#endif