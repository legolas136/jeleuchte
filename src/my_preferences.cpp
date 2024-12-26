#include "my_preferences.h"

Preferences prefs;

// Char	            putChar(const char* key, int8_t value)
// Unsigned Char	putUChar(const char* key, int8_t value)
// Short	        putShort(const char* key, int16_t value)
// Unsigned Short	putUShort(const char* key, uint16_t value)
// Int	            putInt(const char* key, int32_t value)
// Unsigned Int	    putUInt(const char* key, uint32_t value)
// Long	            putLong(const char* key, int32_t value)
// Unsigned Long	putULong(const char* key, uint32_t value)
// Long64	        putLong64(const char* key, int64_t value)
// Unsigned Long64	putULong64(const char* key, uint64_t value)
// Float	        putFloat(const char* key, const float_t value)
// Double	        putDouble(const char* key, const double_t value)
// Bool	            putBool(const char* key, const bool value)
// String	        putString(const char* key, const String value)
// Bytes	        putBytes(const char* key, const void* value, size_t len)

// max prefs value length is 15 chars!

// Network prefs
void prefsInitNetwork()
{
    setupSpiffs();
    Serial.println("Initiating network prefs");
    prefs.begin("network", false);
    prefs.clear();

    prefs.putString("wifi_ssid", "Alice-D");
    prefs.putString("wifi_password", "Multiketaminsaft");

    prefs.end();
    Serial.println("network prefs initialised");
}

void prefsWriteCurrentWifiConfig()
{
    setupSpiffs();
    Serial.println("Writing network prefs");
    prefs.begin("network", false);

    prefs.putString("wifi_ssid", config.wifi_ssid);
    prefs.putString("wifi_password", config.wifi_password);

    prefs.end();
    Serial.println("network prefs written to nvs");
}

bool prefsLoadNetwork()
{
    setupSpiffs();
    Serial.println("Loading network prefs");
    if (prefs.begin("network", true))
    {
        prefs.getString("wifi_ssid", config.wifi_ssid, 32);
        prefs.getString("wifi_password", config.wifi_password, 63);

        prefs.end();
        Serial.println("network prefs loaded");
        return true;
    }
    else
    {
        Serial.println("failed loading network prefs!");
        return false;
    }
}

// Program
void prefsInitProgram()
{
    setupSpiffs();
    Serial.println("Initiating program prefs");
    prefs.begin("program", false);
    prefs.clear();
    prefs.putString("wifi_AP_ssid", getChipID().c_str());
    prefs.putString("wifi_AP_pwd", "0");
    prefs.putString("hostname", "ESP32 Wohnzimmer2");
    prefs.putUShort("rf24_node_address", uint16_t(03));
    prefs.putInt("program", 6);
    prefs.putUChar("g_brightness", uint8_t(255));
    prefs.putUChar("fixed_color_r", uint8_t(255));
    prefs.putUChar("fixed_color_g", uint8_t(32));
    prefs.putUChar("fixed_color_b", uint8_t(0));
    prefs.putUShort("num_leds_conn", uint16_t(60));
    prefs.putULong("deltamillis", 25);

    prefs.end();

    Serial.println("program prefs initialised");
}

// void prefsWriteCurrentProgramConfig()
// {
//     setupSpiffs();
//     Serial.println("Writing program prefs");
//     prefs.begin("program", false);

//     prefs.putString("wifi_AP_ssid", config.wifi_AP_ssid);
//     prefs.putString("wifi_AP_pwd", config.wifi_AP_password);
//     prefs.putString("hostname", config.wifi_hostname);
//     prefs.putString("rf24_node_addr", String(config.rf24_node_address));
//     prefs.putInt("program", config.program);
//     prefs.putUChar("g_brightness", uint8_t(config.global_brightness));
//     prefs.putUChar("fixed_color_r", config.fixed_color_r);
//     prefs.putUChar("fixed_color_g", config.fixed_color_g);
//     prefs.putUChar("fixed_color_b", config.fixed_color_b);
//     prefs.putUShort("num_leds_conn", config.num_leds_connected);
//     prefs.putULong("deltamillis", config.deltamillis);
//     prefs.putUChar("grad_col_1", config.gradient_color_1);
//     prefs.putUChar("grad_col_2", config.gradient_color_2);
//     prefs.putUChar("grad_col_1_br", config.gradient_color_1_brightness);
//     prefs.putUChar("grad_col_2_br", config.gradient_color_2_brightness);
//     prefs.end();
//     Serial.println("program prefs written to nvs");
// }

// bool prefsLoadProgram()
// {
//     setupSpiffs();
//     Serial.println("Loading program prefs");
//     if (prefs.begin("program", true))
//     {
//         if(prefs.getString("wifi_AP_ssid", config.wifi_AP_ssid, 32) == 0)
//         {
//             strcpy(config.wifi_AP_ssid, getChipID().c_str());
//         }
//         prefs.getString("wifi_AP_pwd", config.wifi_AP_password, 63);
//         prefs.getString("hostname", config.wifi_hostname, 64);
//         config.rf24_node_address = uint16_t(strtol(prefs.getString("rf24_node_addr").c_str(), nullptr, 0));
//         config.program = prefs.getInt("program", 6);
//         config.global_brightness = prefs.getUChar("g_brightness", 255);
//         config.fixed_color_r = prefs.getUChar("fixed_color_r", 255);
//         config.fixed_color_g = prefs.getUChar("fixed_color_g", 32);
//         config.fixed_color_b = prefs.getUChar("fixed_color_b", 0);
//         config.num_leds_connected = prefs.getUShort("num_leds_conn", 60);
//         config.deltamillis = prefs.getULong("deltamillis", 25);
//         config.gradient_color_1 = prefs.getUChar("grad_col_1", 0);
//         config.gradient_color_2 = prefs.getUChar("grad_col_2", 255);
//         config.gradient_color_2_brightness = prefs.getUChar("grad_col_2_br", 255);
//         config.gradient_color_1_brightness = prefs.getUChar("grad_col_1_br", 255);

//         prefs.end();
//         Serial.println("program prefs loaded");
//         return true;
//     }
//     else
//     {
//         Serial.println("failed loading program prefs!");
//         return false;
//     }
// }

// etc
void printConfig()
{
    Serial.println("Config:");
    Serial.println(config.wifi_ssid);
    Serial.println(config.wifi_password);
    Serial.println(config.wifi_hostname);
}

void prefsClearWifi()
{
    setupSpiffs();
    prefs.begin("network", false);
    prefs.clear();
    prefs.end();
}

void prefsClearProgram()
{
    setupSpiffs();
    prefs.begin("program", false);
    prefs.clear();
    prefs.end();
}