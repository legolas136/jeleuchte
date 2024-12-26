#include "my_wifi_scan.h"

String found_wifis[10];

void wifi_scan_async()
{
    WiFi.disconnect();
    Serial.println("wifi_scan_async");
    int n = WiFi.scanComplete();
    if (n == -2)
    {
        Serial.print("Scanning for WiFi stations... -> ");
        WiFi.scanNetworks(true);
    }
    else if (n)
    {
        Serial.print(n);
        Serial.println(" stations found");
        for (int i = 0; i < n; i++)
        {
            if (WiFi.SSID(i) == String(config.wifi_ssid))
            {
                Serial.println("Configured station found. Reconnecting now... ");
                WiFi.begin(config.wifi_ssid, config.wifi_password);
                delayMicroseconds(100);
                if (WiFi.waitForConnectResult() == WL_CONNECTED)
                {
                    Serial.println("done!");
                    Serial.print("STA IP: ");
                    Serial.println(WiFi.localIP());
                    Serial.println("Closing AP");
                    WiFi.softAPdisconnect();
                }
            }
            else
            {
                Serial.println("Configured AP not found!");
            }
        }
        WiFi.scanDelete();
        if (WiFi.scanComplete() == -2)
        {
            WiFi.scanNetworks(true);
        }
    }
}

void wifi_scan_blocking()
{
    WiFi.disconnect();
    Serial.println("wifi_scan_blocking");
    int n = WiFi.scanNetworks();
    // WiFi.mode(WIFI_AP_STA);
    Serial.println("scan done");
    if (n == 0)
    {
        Serial.println("no networks found");
    }
    else
    {
        Serial.print(n);
        Serial.println(" networks found");

        for (int i = 0; i < n; ++i)
        {
#ifdef SERIAL_DEBUG
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
#endif
            if (WiFi.SSID(i) == String(config.wifi_ssid))
            {

                Serial.println("Configured AP found.");
                Serial.println("Reconnecting to AP.");
                WiFi.begin(config.wifi_ssid, config.wifi_password);
                delay(100);
                if (WiFi.waitForConnectResult() == WL_CONNECTED)
                {

                    Serial.print("STA IP: ");
                    Serial.println(WiFi.localIP());
                }
            }
            else
            {
                Serial.println("Configured AP not found!");
            }
        }
    }
}

void wifi_scan_portal()
{
    WiFi.disconnect();
    int n = WiFi.scanNetworks();
    // WiFi.mode(WIFI_AP_STA);
    Serial.println("scan done");
    if (n == 0)
    {
        Serial.println("no networks found");
    }
    else
    {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i)
        {
            Serial.println(found_wifis[i]);
            found_wifis[i] = WiFi.SSID(i);
#ifdef SERIAL_DEBUG
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
#endif
        }
    }
}