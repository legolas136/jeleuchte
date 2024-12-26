#include "my_prefs_struct.h"

extern Preferences prefs;
extern my_preferences config;

bool prefs_struct_write(const char *_namespace, const char *_parameter, my_preferences _config)
{
    setupSpiffs();
    Serial.println("Writing struct to nvs");
    //create buffer to hold serialized struct. works if struct is POD
    char buffer[sizeof(my_preferences)];
    ::memcpy(buffer, &_config, sizeof(_config));

    // debug, print the buffer in hex
    for (int x = 0; x < sizeof(_config); x++)
    {
        Serial.printf("%02X ", buffer[x]);
    }

    // open namespace in writable mode
    prefs.begin(_namespace, false);

    // write current struct to prefs nvs
    prefs.putBytes(_parameter, buffer, sizeof(buffer));

    // close namespace
    prefs.end();

    Serial.println("Writing finished");
    return true;
}

bool prefs_struct_read(const char *_namespace, const char *_parameter, my_preferences (&_config))
{
    setupSpiffs();
    // open namespace
    if(!prefs.begin(_namespace, true))
    {
        return false;
    }

    // read (only) size of struct from nvs
    size_t cfgLen = prefs.getBytesLength(_parameter);
    Serial.println(cfgLen);
    // check if nvs size matches the internal config struct size
    if (cfgLen == 0)
    {
        log_e("Config in nvs not present!");
        return false;
    }
    if (cfgLen % sizeof(_config))
    {
        log_e("Config in nvs is in wrong format!");
        return false;
    }

    // create buffer to hold the sequence of bytes read from nvs
    char buffer[cfgLen];

    // read prefs into buffer
    prefs.getBytes(_parameter, buffer, cfgLen);

    // debug: print bytes read in hex
    Serial.println("buffer read: ");
    Serial.println(buffer);
    Serial.println("");
    for (int x = 0; x < cfgLen; x++)
        Serial.printf("%02X ", buffer[x]);

    ::memcpy(&_config, buffer, sizeof(_config)); // variant 2a

    // close namespace
    Serial.println("read end");
    prefs.end();
    return true;
}

bool prefs_struct_clear(const char* _namespace, const char* _parameter)
{
    setupSpiffs();
    // open namespace in writable mode
    if(!prefs.begin(_namespace, false))
    {
        return false;
    }

    // clear containing blobs
    prefs.clear();

    prefs.end();
    return true;
}

// bool setDefaultValues()
// {
//     config.autosave_enabled = false;
//     config.global_brightness = 255;
//     config.gradient_color_1 = 0;
//     config.gradient_color_1_brightness = 255;
//     config.gradient_color_2 = 255;
//     config.gradient_color_2_brightness = 255;
//     config.fixed_color_r = 255;
//     config.fixed_color_g = 123;
//     config.fixed_color_b = 0;
//     config.program = 6;
//     config.rf24_node_address = 01;
//     config.num_leds_connected = 30;
//     return true;
// }

bool autosave_ifenabled()
{
    if(config.autosave_enabled)
    {
    prefs_struct_clear();
    prefs_struct_write();
    }
    return true;
}