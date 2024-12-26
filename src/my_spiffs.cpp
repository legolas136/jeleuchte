#include "my_spiffs.h"

char key_chararray[128];
char value_chararray[128];
// uint16_t SPIFFSVersion();

void setupSpiffs()
{
    static bool spiffsIsMounted = false;

    if (spiffsIsMounted == false)
    {
        if (!SPIFFS.begin(true))
        {
            Serial.println("An Error has occurred while mounting SPIFFS");
            return;
        }
        else
        {
            spiffsIsMounted = true;
        }
    }
}

int getSPIFFSVersion()
{
    File inifile = SPIFFS.open("/versioning_spiffs.txt");
    String line ="";
    line = inifile.readString();
    // while (inifile.available())
    // {
    //     line = inifile.readStringUntil('\n'); 
    //     // configIniParseLine(line.c_str());
    // }
    inifile.close();
    return(String(line).toInt());
}

bool configIniCheckExistence()
{
    if (SPIFFS.exists("/config.ini"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void configIniCreateNew()
{
    // create config.ini -> open in "w" (write mode)
    File TempFile = SPIFFS.open("/config.ini", "w");
    TempFile.println("#empty config");
    TempFile.println("ssid = xxx");
    TempFile.println("passwort = xxx");
    TempFile.close();
}

void configIniRead(const char *configfile)
{
    File inifile = SPIFFS.open(configfile, "r");
    String line;
    while (inifile.available())
    {
        line = inifile.readStringUntil('\n');
        configIniParseLine(line.c_str());
    }
    inifile.close();
}

void configIniWriteWifiConfig()
{
    File inifile = SPIFFS.open("/wifi.ini", "w");

    inifile.print("wifi_ssid = ");
    inifile.println(config.wifi_ssid);
    inifile.print("wifi_password = ");
    inifile.println(config.wifi_password);

    inifile.flush();
    inifile.close();
}

void configIniWriteProgramConfig()
{
    File inifile = SPIFFS.open("/config.ini", "w");
    inifile.print("wifi_hostname = ");
    inifile.println(config.wifi_hostname);
    inifile.print("wifi_AP_ssid = ");
    inifile.println(config.wifi_AP_ssid);
    inifile.print("wifi_AP_password = ");
    inifile.println(config.wifi_AP_password);
    inifile.print("rf24_node_address = ");
    inifile.print("0");
    inifile.println(config.rf24_node_address, 8);
    inifile.print("program = ");
    inifile.println(config.program);
    inifile.print("global_brightness = ");
    inifile.println(config.global_brightness);
    inifile.print("fixed_color_r = ");
    inifile.println(config.fixed_color_r);
    inifile.print("fixed_color_g = ");
    inifile.println(config.fixed_color_g);
    inifile.print("fixed_color_b = ");
    inifile.println(config.fixed_color_b);
    inifile.print("deltamillis = ");
    inifile.println(config.deltamillis);
    inifile.print("brightness = ");
    inifile.println(config.brightness);
    inifile.print("num_leds_connected = ");
    inifile.println(config.num_leds_connected);

    inifile.flush();
    inifile.close();
}

void configIniParseLine(const char *str)
{
    char *cursor_ptr; // a ptr, imagine a cursor

    cursor_ptr = strstr(str, "="); // check if line contains a "="
    if (cursor_ptr)
    {
        *cursor_ptr = '\0'; // replace "=" with a \0 to separate command from value
        cursor_ptr++;       // move cursor one char further to be in the value-part of the line
    }
    else
    {
        // ????
        cursor_ptr = (char *)"0"; // No value, assume zero
    }

    // strings to hold the found key and its value
    String key;
    String value;

    int inx; // Index in string

    key = str;

    if ((inx = key.indexOf("#")) >= 0) // Comment line or partial comment?
    {
        key.remove(inx); // Yes, remove
    }

    key.trim(); // Remove spaces and CR

    if (key.length() == 0) // Lege commandline (comment)?
    {
        return;
    }

    // key.toLowerCase(); // Force to lower case

    // value = chomp ( val ) ;                             // Get the specified value
    value = cursor_ptr;
    if ((inx = value.indexOf("#")) >= 0) // Comment line or partial comment?
    {
        value.remove(inx); // Yes, remove
    }
    value.trim(); // Remove spaces and CR

    if (value.length())
    {
        Serial.println("Einstellung: " + key + " Wert: " + value);
    }
    else
    {
        Serial.println("Einstellung: " + key + " ohne Wert ");
    }
    configIniSetData(key, value);
}

void configIniSetData(String key, String value)
{
    if (key.indexOf("wifi_ssid") >= 0)
        strcpy(config.wifi_ssid, value.c_str());
    else if (key.indexOf("wifi_password") >= 0)
        strcpy(config.wifi_password, value.c_str());
    else if (key.indexOf("wifi_AP_ssid") >= 0)
        strcpy(config.wifi_AP_ssid, value.c_str());
    else if (key.indexOf("wifi_AP_password") >= 0)
        strcpy(config.wifi_AP_password, value.c_str());
    else if (key.indexOf("wifi_hostname") >= 0)
        strcpy(config.wifi_hostname, value.c_str());
    else if (key.indexOf("wifi_auto_reconnect") >= 0)
        config.wifi_auto_reconnect = bool(atoi(value.c_str()));
    else if (key.indexOf("rf24_node_address") >= 0)
        config.rf24_node_address = uint16_t(strtol(value.c_str(), nullptr, 0));
    else if (key.indexOf("program") >= 0)
        config.program = atoi(value.c_str());
    else if (key.indexOf("global_brightness") >= 0)
        config.global_brightness = uint8_t(atoi(value.c_str()));
    else if (key.indexOf("fixed_color_r") >= 0)
        config.fixed_color_r = uint8_t(atoi(value.c_str()));
    else if (key.indexOf("fixed_color_g") >= 0)
        config.fixed_color_g = uint8_t(atoi(value.c_str()));
    else if (key.indexOf("fixed_color_b") >= 0)
        config.fixed_color_b = uint8_t(atoi(value.c_str()));
    else if (key.indexOf("deltamillis") >= 0)
        config.deltamillis = uint32_t(atoi(value.c_str()));
    else if (key.indexOf("brightness") >= 0)
        config.brightness = atoi(value.c_str());
    else if (key.indexOf("num_leds_connected") >= 0)
        config.num_leds_connected = uint16_t(atoi(value.c_str()));
}

void configIniDelete()
{
    if (SPIFFS.exists("/config.ini"))
    {
        SPIFFS.remove("/config.ini");
    }
}

void printCurrentConfig()
{
    Serial.print("wifi_ssid = ");
    Serial.println(config.wifi_ssid);
    Serial.print("wifi_password = ");
    Serial.println(config.wifi_password);
    Serial.print("wifi_AP_ssid = ");
    Serial.println(config.wifi_AP_ssid);
    Serial.print("wifi_AP_password = ");
    Serial.println(config.wifi_AP_password);
    Serial.print("wifi_hostname = ");
    Serial.println(config.wifi_hostname);
    Serial.print("rf24_node_address = ");
    Serial.println(config.rf24_node_address);
    Serial.print("program = ");
    Serial.println(config.program);
    Serial.print("global_brightness = ");
    Serial.println(config.global_brightness);
    Serial.print("fixed_color_r = ");
    Serial.println(config.fixed_color_r);
    Serial.print("fixed_color_g = ");
    Serial.println(config.fixed_color_g);
    Serial.print("fixed_color_b = ");
    Serial.println(config.fixed_color_b);
    Serial.print("deltamillis = ");
    Serial.println(config.deltamillis);
    Serial.print("brightness = ");
    Serial.println(config.brightness);
    Serial.print("num_leds_connected = ");
    Serial.println(config.num_leds_connected);
}
