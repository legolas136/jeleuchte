#include "my_webserver.h"

extern bool update_needed;
extern bool spiffs_update_needed;
extern LedTargetSettings staticColors;

// ASync Webserver related
const char *PARAM_INPUT_1 = "output";
const char *PARAM_INPUT_2 = "class";
const char *PARAM_INPUT_3 = "id";
const char *PARAM_INPUT_4 = "value";
const char *PARAM_INPUT_5 = "r";
const char *PARAM_INPUT_6 = "g";
const char *PARAM_INPUT_7 = "b";
const char *PARAM_INPUT_8 = "remote";
const char *PARAM_INPUT_9 = "iswifi";
const char *PARAM_INPUT_10 = "ssid_index";
const char *PARAM_INPUT_11 = "password";
const char *PARAM_INPUT_12 = "config_key";
const char *PARAM_INPUT_13 = "config_value";
const char *PARAM_INPUT_14 = "config_message";
const char *PARAM_INPUT_15 = "h";
const char *PARAM_INPUT_16 = "s";
const char *PARAM_INPUT_17 = "v";
const char *PARAM_INPUT_18 = "onTime";
const char *PARAM_INPUT_19 = "offTime";
const char *PARAM_INPUT_20 = "repeats";

const char *serverIndex = "<form method='POST' action='/updatefirmware' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";

AsyncWebServer server(ASYNC_WEBSERVER_PORT); // Create/Setup AsyncWebServer object on port 80
// AsyncElegantOtaClass AsyncElegantOTA;

// ----------------------------------------------------------------------------------------------------------------------------------------
AsyncWebSocket ws("/ws");
JsonDocument testJson;

void notifyClients(String sensorReadings)
{
      ws.textAll(sensorReadings);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    // tickWebSockets();
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    // tickWebSockets();
    data[len] = 0;
    String message = (char*)data;
    // Check if the message is "getTest"
    if (strcmp((char*)data, "getTest") == 0) {
    //   if it is, send current sensor readings
      String sensorReadings = "First ws message";
      Serial.print(sensorReadings);
      notifyClients(sensorReadings);
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
      switch (type) {
        case WS_EVT_CONNECT:
          Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
          break;
        case WS_EVT_DISCONNECT:
          Serial.printf("WebSocket client #%u disconnected\n", client->id());
          break;
        case WS_EVT_DATA:
          handleWebSocketMessage(arg, data, len);
          break;
        case WS_EVT_PONG:
        case WS_EVT_ERROR:
          break;
      }
}

void initWebSocket()
{
    ws.onEvent(onEvent);
    server.addHandler(&ws);
}
extern unsigned long global_fps;
void tickWebSockets()
{
    static uint32_t test = 0;
    static uint32_t lastmillis = millis();
    if (millis() - lastmillis > 1000)
    {
        notifyClients(String(global_fps));
        test++;
        ws.cleanupClients();
        lastmillis = millis();
    }
}
void sendOverWebsockets(String message)
{
        notifyClients(message);
        ws.cleanupClients();


}

// ----------------------------------------------------------------------------------------------------------------------------------------

// processor to replace placeholders in html file %PLACEHOLDER%
String processor(const String &var)
{
    if (1) // Variables
    {
        if (var == "EXAMPLE")
        {
            String EXAMPLE = "";
            EXAMPLE += "";
            return EXAMPLE;
        }
        // program-specific placeholders are found in included cpp file:

        // Replaces placeholder in html file

        if (var == "PROG_BUILD_NUMBER")
        {
            String PROG_BUILD_NUMBER = "";
            PROG_BUILD_NUMBER += BUILD_NUMBER;
            return PROG_BUILD_NUMBER;
        }

        if (var == "PROG_VERSION")
        {
            String PROG_VERSION = "";
            PROG_VERSION += VERSION;
            return PROG_VERSION;
        }

        if (var == "PROG_VERSION_SHORT")
        {
            String PROG_VERSION_SHORT = "";
            PROG_VERSION_SHORT += VERSION_SHORT;
            return PROG_VERSION_SHORT;
        }

        if (var == "SPIFFS_BUILD_NUMBER")
        {
            String SPIFFS_BUILD_NUMBER = "";
            SPIFFS_BUILD_NUMBER += getSPIFFSVersion();
            // SPIFFS_BUILD_NUMBER += 123;
            return SPIFFS_BUILD_NUMBER;
        }

        if (var == "SPIFFS_VERSION")
        {
            String SPIFFS_VERSION = "";
            SPIFFS_VERSION += VERSION_SPIFFS;
            return SPIFFS_VERSION;
        }

        if (var == "SPIFFS_VERSION_SHORT")
        {
            String SPIFFS_VERSION_SHORT = "";
            SPIFFS_VERSION_SHORT += VERSION_SHORT_SPIFFS;
            return SPIFFS_VERSION_SHORT;
        }

        if (var == "PROGRAMM")
        {
            String PROGRAMM = "";
            PROGRAMM += config.program;
            return PROGRAMM;
        }

        if (var == "BR_MODE")
        {
            String BR_MODE = "";
            BR_MODE += dsp.brModeOn;
            return BR_MODE;
        }

        if (var == "UPDATE_SERVER")
        {
            String UPDATE_SERVER = "";
            UPDATE_SERVER += config.fw_update_server;
            return UPDATE_SERVER;
        }

        if (var == "DELTAMILLIS")
        {
            String DELTAMILLIS = "";
            DELTAMILLIS += config.deltamillis;
            return DELTAMILLIS;
        }

        if (var == "BRIGHTNESS")
        {
            String BRIGHTNESS = "";
            BRIGHTNESS += config.global_brightness;
            return BRIGHTNESS;
        }

        if (var == "PWM_BRIGHTNESS")
        {
            String PWM_BRIGHTNESS = "";
            PWM_BRIGHTNESS += config.pwm_brightness;
            return PWM_BRIGHTNESS;
        }

        if (var == "BANDS_MULTI0")
        {
            String BANDS_MULTI0 = "";
            BANDS_MULTI0 += dsp.bands_multi[0];
            return BANDS_MULTI0;
        }

        if (var == "AP_SSID")
        {
            String AP_SSID = "";
            AP_SSID += config.wifi_AP_ssid;
            return AP_SSID;
        }

        if (var == "HOSTNAME")
        {
            String HOSTNAME = "";
            HOSTNAME += config.wifi_hostname;
            return HOSTNAME;
        }

        if (var == "AP_IP")
        {
            String AP_IP = "";
            AP_IP += WiFi.softAPIP().toString();
            return AP_IP;
        }

        if (var == "STA_SSID")
        {
            String STA_SSID = "";
            STA_SSID += config.wifi_ssid;
            return STA_SSID;
        }

        if (var == "FOUND_WIFI_SSID_0")
        {
            String FOUND_WIFI_SSID_0 = "";
            FOUND_WIFI_SSID_0 += found_wifis[0];
            return FOUND_WIFI_SSID_0;
        }

        if (var == "FOUND_WIFI_SSID_1")
        {
            String FOUND_WIFI_SSID_1 = "";
            FOUND_WIFI_SSID_1 += found_wifis[1];
            return FOUND_WIFI_SSID_1;
        }

        if (var == "FOUND_WIFI_SSID_2")
        {
            String FOUND_WIFI_SSID_2 = "";
            FOUND_WIFI_SSID_2 += found_wifis[2];
            return FOUND_WIFI_SSID_2;
        }

        if (var == "FOUND_WIFI_SSID_3")
        {
            String FOUND_WIFI_SSID_3 = "";
            FOUND_WIFI_SSID_3 += found_wifis[3];
            return FOUND_WIFI_SSID_3;
        }

        if (var == "FOUND_WIFI_SSID_4")
        {
            String FOUND_WIFI_SSID_4 = "";
            FOUND_WIFI_SSID_4 += found_wifis[4];
            return FOUND_WIFI_SSID_4;
        }

        if (var == "FOUND_WIFI_SSID_5")
        {
            String FOUND_WIFI_SSID_5 = "";
            FOUND_WIFI_SSID_5 += found_wifis[5];
            return FOUND_WIFI_SSID_5;
        }

        if (var == "FOUND_WIFI_SSID_6")
        {
            String FOUND_WIFI_SSID_6 = "";
            FOUND_WIFI_SSID_6 += found_wifis[6];
            return FOUND_WIFI_SSID_6;
        }

        if (var == "FOUND_WIFI_SSID_7")
        {
            String FOUND_WIFI_SSID_7 = "";
            FOUND_WIFI_SSID_7 += found_wifis[7];
            return FOUND_WIFI_SSID_7;
        }

        if (var == "FOUND_WIFI_SSID_8")
        {
            String FOUND_WIFI_SSID_8 = "";
            FOUND_WIFI_SSID_8 += found_wifis[8];
            return FOUND_WIFI_SSID_8;
        }

        if (var == "FOUND_WIFI_SSID_9")
        {
            String FOUND_WIFI_SSID_9 = "";
            FOUND_WIFI_SSID_9 += found_wifis[9];
            return FOUND_WIFI_SSID_9;
        }

        if (var == "STA_IP")
        {
            String STA_IP = "";
            STA_IP += WiFi.localIP().toString();
            return STA_IP;
        }

        if (var == "FPS")
        {
            String FPS = "";
            FPS += last_fps;
            return FPS;
        }

        if (var == "FPS_RF24")
        {
            String FPS_RF24 = "";
            FPS_RF24 += last_rf24_fps;
            return FPS_RF24;
        }

        if (var == "R_VALUE")
        {
            String R_VALUE = "";
            R_VALUE += config.fixed_color_r;
            return R_VALUE;
        }

        if (var == "G_VALUE")
        {
            String G_VALUE = "";
            G_VALUE += config.fixed_color_g;
            return G_VALUE;
        }

        if (var == "B_VALUE")
        {
            String B_VALUE = "";
            B_VALUE += config.fixed_color_b;
            return B_VALUE;
        }

        if (var == "B_VALUE")
        {
            String B_VALUE = "";
            B_VALUE += config.fixed_color_b;
            return B_VALUE;
        }

        if (var == "BASSHUE")
        {
            String BASSHUE = "";
            BASSHUE += config.hue_bass;
            return BASSHUE;
        }

        if (var == "MIDHUE")
        {
            String MIDHUE = "";
            MIDHUE += config.hue_mid;
            return MIDHUE;
        }

        if (var == "TREBLEHUE")
        {
            String TREBLEHUE = "";
            TREBLEHUE += config.hue_treble;
            return TREBLEHUE;
        }

        if (var == "BRMODEFALLINGSPEED")
        {
            String BRMODEFALLINGSPEED = "";
            BRMODEFALLINGSPEED += dsp.brModeFallingSpeed;
            return BRMODEFALLINGSPEED;
        }

        if (var == "BASSFALLINGSPEED")
        {
            String BASSFALLINGSPEED = "";
            BASSFALLINGSPEED += dsp.bassFallingSpeed;
            return BASSFALLINGSPEED;
        }

        if (var == "MIDFALLINGSPEED")
        {
            String MIDFALLINGSPEED = "";
            MIDFALLINGSPEED += dsp.midFallingSpeed;
            return MIDFALLINGSPEED;
        }

        if (var == "TREBLEFALLINGSPEED")
        {
            String TREBLEFALLINGSPEED = "";
            TREBLEFALLINGSPEED += dsp.trebleFallingSpeed;
            return TREBLEFALLINGSPEED;
        }

        if (var == "BANDSLEVELZOOMFACTOR")
        {
            String BANDSLEVELZOOMFACTOR = "";
            BANDSLEVELZOOMFACTOR += dsp.bands_level_zoom_factor;
            return BANDSLEVELZOOMFACTOR;
        }

        if (var == "BANDSLEVELOFFSET")
        {
            String BANDSLEVELOFFSET = "";
            BANDSLEVELOFFSET += dsp.bands_level_offset;
            return BANDSLEVELOFFSET;
        }

        if (var == "RF24_CONNECTED")
        {
            String RF24_CONNECTED = "";
            RF24_CONNECTED += radio.isChipConnected();
            return RF24_CONNECTED;
        }

        if (var == "RF24_CHANNEL")
        {
            String RF24_CHANNEL = "";
            RF24_CHANNEL += radio.getChannel();
            return RF24_CHANNEL;
        }

        if (var == "RF24_DATA_RATE")
        {
            String RF24_DATA_RATE = "";
            switch (radio.getDataRate())
            {
            case 0:
            {
                RF24_DATA_RATE += "1 Mbps";
                break;
            }
            case 1:
            {
                RF24_DATA_RATE += "2 Mbps";
                break;
            }
            case 2:
            {
                RF24_DATA_RATE += "250 Kbps";
                break;
            }
            }
            return RF24_DATA_RATE;
        }

        if (var == "RF24_PA_LEVEL")
        {
            String RF24_PA_LEVEL = "";
            switch (radio.getPALevel())
            {
            case 0:
            {
                RF24_PA_LEVEL += "min";
                break;
            }
            case 1:
            {
                RF24_PA_LEVEL += "low";
                break;
            }
            case 2:
            {
                RF24_PA_LEVEL += "high";
                break;
            }
            case 3:
            {
                RF24_PA_LEVEL += "max";
                break;
            }
            }

            return RF24_PA_LEVEL;
        }

        if (var == "UPDATE_SERVER")
        {
            String UPDATE_SERVER = "";
            UPDATE_SERVER += config.fw_update_server;
            return UPDATE_SERVER;
        }

        if (var == "UPDATE_SERVER_SPIFFS")
        {
            String UPDATE_SERVER_SPIFFS = "";
            UPDATE_SERVER_SPIFFS += config.spiffs_update_server;
            return UPDATE_SERVER_SPIFFS;
        }

        if (var == "RF24_NODE_ADDRESS")
        {
            String RF24_NODE_ADDRESS = "";
            RF24_NODE_ADDRESS += config.rf24_node_address;
            return RF24_NODE_ADDRESS;
        }

        if (var == "WIFI_HOSTNAME")
        {
            String WIFI_HOSTNAME = "";
            WIFI_HOSTNAME += config.wifi_hostname;
            return WIFI_HOSTNAME;
        }

        if (var == "AUTOSAVE_ENABLED")
        {
            String AUTOSAVE_ENABLED = "";
            AUTOSAVE_ENABLED += config.autosave_enabled;
            return AUTOSAVE_ENABLED;
        }

        if (var == "LED_BED_MODE")
        {
            String LED_BED_MODE = "";
            LED_BED_MODE += config.led_bed_mode;
            return LED_BED_MODE;
        }
    }
    return String();
}

// Sets up webserver & handling
void setupWebServer()
{
    if (1) // Files
    {
        setupSpiffs();
        //------------- files -----------------------------------------------------------------------------------------------
        // /index.html
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(SPIFFS, "/index.html", String(), false, processor); });
        server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(SPIFFS, "/index.html", String(), false, processor); });
        // /index_mobile.html
        server.on("/index_mobile.html", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(SPIFFS, "/index_mobile.html", String(), false, processor); });

        // // /portal.html
        // server.on("/portal.html", HTTP_GET, [](AsyncWebServerRequest *request)
        //           {
        //               wifi_auto_reconnect = false;
        //               delay(1000);
        //               wifi_scan_portal();
        //               delay(1000);
        //               request->send(SPIFFS, "/portal.html", String(), false, processor);
        //           });
        // //-----------------------------------------------------------------------------------

        // /serverIndex
        // opens the Elegant OTA interface
        // page is stored in string "serverIndex"
        server.on("/serverIndex", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(200, "text/html", serverIndex); });

        // /led_control.html
        server.on("/led_control.html", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(SPIFFS, "/led_control.html", String(), false, processor); });
        // /code.js
        server.on("/code.js", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(SPIFFS, "/code.js", "text/javascript"); });
        // /jscolor.js
        server.on("/jscolor.js", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(SPIFFS, "/jscolor.js", "text/javascript"); });
        // /FileSaver.js
        server.on("/FileSaver.js", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(SPIFFS, "/FileSaver.js", "text/javascript"); });
        //websocket.js
        server.on("/websocket.js", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(SPIFFS, "/websocket.js", "text/javascript"); });
        // /style.css
        server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(SPIFFS, "/style.css", "text/css"); });
        // /style_mobile.css
        server.on("/style_mobile.css", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(SPIFFS, "/style_mobile.css", "text/css"); });
        // /portal.css
        server.on("/portal.css", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(SPIFFS, "/portal.css", "text/css"); });
        // /config.ini
        server.on("/config.ini", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(SPIFFS, "/config.ini", "text/plain"); });
        // /wifi_example.ini
        server.on("/wifi_example.ini", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(SPIFFS, "/wifi_example.ini", "text/plain"); });
        //     //------------- filesend --------------------------------------------------------------------------------------------
    }
    if (1) // Commands
    {
        //------------- commands --------------------------------------------------------------------------------------------

        server.on("/param", HTTP_GET, [](AsyncWebServerRequest *request)
                  {
                      String inputMessage1;
                      String inputMessage2;
                      String inputMessage3;
                      String inputMessage4;
                      String inputMessage5;
                      String inputMessage6;
                      String inputMessage7;
                      String inputMessage8;

                      // id&value: Power button, Brightness, Programm, Save config, delta_millis
                      if (request->hasParam(PARAM_INPUT_3) && request->hasParam(PARAM_INPUT_4))
                      {
                          inputMessage1 = request->getParam(PARAM_INPUT_3)->value();
                          inputMessage2 = request->getParam(PARAM_INPUT_4)->value();

                          //   if (global_remote)
                          //   {
                          //       for (int i = 0; i < vislink_data.amount_of_vislinks_found; i++)
                          //       {
                          //           http_request2(vislink_data.ips[i], "update", inputMessage1, inputMessage2);
                          //       }
                          //   }

                          if (inputMessage1 == "power_button")
                          {
                              if (inputMessage2 == "1")
                              {
                                  power_switch = true;
                              }
                              else if (inputMessage2 == "0")
                              {
                                  ledsOff();
                              }
                          }
                          if (inputMessage1 == "brightness")
                          {
                              setGlobalBrightness(inputMessage2.toInt());
                          }
                          if (inputMessage1 == "pwm_brightness")
                          {
                              config.pwm_brightness = inputMessage2.toFloat();
                          }
                          if (inputMessage1 == "program")
                          {
                              setProgram(inputMessage2.toInt());
                          }
                          if (inputMessage1 == "save_config" && inputMessage2 == "1")
                          {
                              configIniWriteWifiConfig();
                              configIniWriteProgramConfig();
                              prefsWriteCurrentWifiConfig();
                              // prefsWriteCurrentProgramConfig();
                          }
                          if (inputMessage1 == "erase_config" && inputMessage2 == "1")
                          {
                              configIniDelete();
                              prefsClearWifi();
                              prefsClearProgram();
                          }
                          if (inputMessage1 == "br_mode")
                          {
                              dsp.brModeOn = inputMessage2.toInt();
                          }
                          if (inputMessage1 == "br_mode_pwm")
                          {
                              dsp.brModePwmOn = inputMessage2.toInt();
                          }
                          if (inputMessage1 == "brModeFallingSpeed")
                          {
                              dsp.brModeFallingSpeed = inputMessage2.toInt();
                          }
                          if (inputMessage1 == "bassFallingSpeed")
                          {
                              dsp.bassFallingSpeed = inputMessage2.toInt();
                          }
                          if (inputMessage1 == "midFallingSpeed")
                          {
                              dsp.midFallingSpeed = inputMessage2.toInt();
                          }
                          if (inputMessage1 == "trebleFallingSpeed")
                          {
                              dsp.trebleFallingSpeed = inputMessage2.toInt();
                          }
                          if (inputMessage1 == "bassHue")
                          {
                              config.hue_bass = inputMessage2.toInt();
                          }
                          if (inputMessage1 == "midHue")
                          {
                              config.hue_mid = inputMessage2.toInt();
                          }
                          if (inputMessage1 == "trebleHue")
                          {
                              config.hue_treble = inputMessage2.toInt();
                          }
                          if (inputMessage1 == "accumulation_mode_bass")
                          {
                              config.accumulation_mode_bass = inputMessage2.toInt();
                          }
                          if (inputMessage1 == "accumulation_mode_mid")
                          {
                              config.accumulation_mode_mid = inputMessage2.toInt();
                          }
                          if (inputMessage1 == "accumulation_mode_treble")
                          {
                              config.accumulation_mode_treble = inputMessage2.toInt();
                          }
                          if (inputMessage1 == "accumulation_mode_brmode")
                          {
                              config.accumulation_mode_br_mode = inputMessage2.toInt();
                          }
                          if (inputMessage1 == "led_bed_mode")
                          {
                              config.led_bed_mode = inputMessage2.toInt();
                          }
                          if (inputMessage1 == "deltaMillis")
                          {
                              config.deltamillis = inputMessage2.toInt();
                          }
                          if (inputMessage1 == "ssid_found_index")
                          {
                    //   int n = inputMessage2.toInt();
                    //   strcpy(wifi_ssid, found_wifis[n].c_str());

#ifdef SERIAL_DEBUG
                              Serial.print("Debug: wifi_ssid set to: ");
                              Serial.println(wifi_ssid);
#endif
                          }
                          if (inputMessage1 == "ssid")
                          {
                              inputMessage2.toCharArray(config.wifi_ssid, inputMessage2.length() + 1);
                              prefsWriteCurrentWifiConfig();

#ifdef SERIAL_DEBUG
                              Serial.print("Debug: wifi_ssid set to: ");
                              Serial.println(wifi_ssid);
#endif
                          }
                          if (inputMessage1 == "enter_hostname")
                          {
                              inputMessage2.toCharArray(config.wifi_hostname, inputMessage2.length() + 1);
                              prefsWriteCurrentWifiConfig();

                              Serial.print("Debug: wifi_hostname set to: ");
                              Serial.println(config.wifi_hostname);
                          }
                          if (inputMessage1 == "password")
                          {
                              inputMessage2.toCharArray(config.wifi_password, inputMessage2.length() + 1);
                              prefsWriteCurrentWifiConfig();
                              setupWifi();

#ifdef SERIAL_DEBUG
                              Serial.print("Debug: wifi_password set to: ");
                              Serial.println(wifi_password);
#endif
                          }
                          if (inputMessage1 == "AP_ssid")
                          {
                              inputMessage2.toCharArray(config.wifi_AP_ssid, inputMessage2.length() + 1);
                              Serial.print("Debug: AP_ssid set to: ");
                              Serial.println(config.wifi_AP_ssid);
                          }
                          if (inputMessage1 == "AP_password")
                          {
                              inputMessage2.toCharArray(config.wifi_AP_password, inputMessage2.length() + 1);
                          }
                          if (inputMessage1 == "reset")
                          {
                              request->send(200, "text/plain", "OK");
                              ESP.restart();
                          }
                          if (inputMessage1 == "printDebug")
                          {
                              //   mqtttest();
                          }
                          if (inputMessage1 == "enableAP")
                          {
                              WiFi.enableAP(inputMessage2.toInt());
                          }
                          if (inputMessage1 == "configIniRead")
                          {
                              configIniRead();
                          }
                          if (inputMessage1 == "led_amount")
                          {
                              config.num_leds_connected = inputMessage2.toInt();
                              blanken();
                          }
                          if (inputMessage1 == "led_color_order")
                          {
                              config.led_color_order = inputMessage2.toInt();
                              prefs_struct_write();
                              delay(100);
                              ESP.restart();
                          }
                          if (inputMessage1 == "reset_band_multiplicators")
                          {
                              for (int i = 0; i < 7; i++)
                              {
                                  dsp.bands_multi[i] = 127;
                              }
                              dsp.bands_level_zoom_factor = 1.0f;
                              dsp.bands_level_offset = 0;
                          }
                          if (inputMessage1 == "bands_level_zoom_factor")
                          {
                              dsp.bands_level_zoom_factor = inputMessage2.toFloat();
                          }
                          if (inputMessage1 == "bands_level_offset")
                          {
                              dsp.bands_level_offset = inputMessage2.toInt();
                          }
                          if (inputMessage1 == "rf24_node_address")
                          {
                              Serial.println("got node address");
                              config.rf24_node_address = uint16_t(inputMessage2.toInt());
                              Serial.print("Set rf24_node_address to: ");
                              Serial.println(config.rf24_node_address);
                          }
                          if (inputMessage1 == "save_wifi_prefs")
                          {
                              prefsWriteCurrentWifiConfig();
                          }
                          if (inputMessage1 == "load_wifi_prefs")
                          {
                              prefsLoadNetwork();
                          }
                          if (inputMessage1 == "delete_wifi_prefs")
                          {
                              prefsClearWifi();
                          }
                          if (inputMessage1 == "save_program_prefs")
                          {
                              // prefsWriteCurrentProgramConfig();
                          }
                          if (inputMessage1 == "load_program_prefs")
                          {
                              // prefsLoadProgram();
                          }
                          if (inputMessage1 == "delete_program_prefs")
                          {
                              prefsClearProgram();
                              // prefsLoadProgram();     // will load standard prefs this time
                          }
                          if (inputMessage1 == "write_wifi_ini")
                          {
                              configIniWriteWifiConfig();
                          }
                          if (inputMessage1 == "read_wifi_ini")
                          {
                              configIniRead("/wifi.ini");
                          }
                          if (inputMessage1 == "write_config_ini")
                          {
                              configIniWriteProgramConfig();
                          }
                          if (inputMessage1 == "read_config_ini")
                          {
                              configIniRead("/config.ini");
                          }
                          if (inputMessage1 == "tryFuncMappings")
                          {
                              Serial.println("Trying Out function mapping strTorFunc: int 7 & int 5");
                              Serial.println(strToFunc(inputMessage2.c_str(), 7, 5));
                              Serial.println("done.");
                          }
                          if (inputMessage1 == "dimUp")
                          {
                              dimUp(uint8_t(inputMessage2.toInt()));
                          }
                          if (inputMessage1 == "dimDown")
                          {
                              dimDown(uint8_t(inputMessage2.toInt()));
                          }
                          if (inputMessage1 == "programIncrease")
                          {
                              programIncrease();
                          }
                          if (inputMessage1 == "programDecrease")
                          {
                              programDecrease();
                          }
                          if (inputMessage1 == "prefsStructWrite")
                          {
                              prefs_struct_clear();
                              prefs_struct_write();
                          }
                          if (inputMessage1 == "prefsStructRead")
                          {
                              prefs_struct_read();
                          }
                          if (inputMessage1 == "prefsStructClear")
                          {
                              prefs_struct_clear();
                          }
                          if (inputMessage1 == "httpFwUpdate")
                          {
                              update_needed = true;
                          }
                          if (inputMessage1 == "httpSpiffsUpdate")
                          {
                              spiffs_update_needed = true;
                          }
                          if (inputMessage1 == "enterUpdateServer")
                          {
                              inputMessage2.toCharArray(config.fw_update_server, inputMessage2.length() + 1);
                              Serial.print("New update server: ");
                              Serial.println(config.fw_update_server);
                          }
                          if (inputMessage1 == "enterSpiffsServer")
                          {
                              inputMessage2.toCharArray(config.spiffs_update_server, inputMessage2.length() + 1);
                              Serial.print("New spiffs server: ");
                              Serial.println(config.spiffs_update_server);
                          }
                          if (inputMessage1 == "controlAutosave")
                          {
                              config.autosave_enabled = inputMessage2.toInt();
                              Serial.print("Autosave Status: ");
                              Serial.println(config.autosave_enabled);
                          }
                          // http://192.168.1.78/param?id=led_alarm_active&value=xxx
                          if (inputMessage1 == "led_alarm_active")
                          {
                              if (power_switch)
                              {
                                  led_alarm_active = 1;
                              }
                          }
                      }

                      // class, id & value: bands_multi
                      if (request->hasParam(PARAM_INPUT_2) && request->hasParam(PARAM_INPUT_3) && request->hasParam(PARAM_INPUT_4))
                      {

                          inputMessage1 = request->getParam(PARAM_INPUT_2)->value();
                          inputMessage2 = request->getParam(PARAM_INPUT_3)->value();
                          inputMessage3 = request->getParam(PARAM_INPUT_4)->value();

                          if (inputMessage1 == "bands_multi")
                          {
                              dsp.bands_multi[inputMessage2.toInt()] = inputMessage3.toInt();
                          }
                      }

                      if (request->hasParam(PARAM_INPUT_9) && request->hasParam(PARAM_INPUT_10) && request->hasParam(PARAM_INPUT_11))
                      {
                          inputMessage1 = request->getParam(PARAM_INPUT_9)->value();
                          inputMessage2 = request->getParam(PARAM_INPUT_10)->value();
                          inputMessage3 = request->getParam(PARAM_INPUT_11)->value();
                          Serial.println("Wifi Found");
                          Serial.println(inputMessage2);
                          Serial.println(inputMessage3);

                          //                inputMessage2.toCharArray(wifi_ssid, inputMessage2.length() + 1);
                          //   int n = inputMessage2.toInt();
                          //   strcpy(wifi_ssid, found_wifis[n].c_str());
                          //   inputMessage3.toCharArray(wifi_password, inputMessage3.length() + 1);
                          //   saveConfig();
                          //   setupWifi();
                      }
                      // RGB-Values
                      if (request->hasParam(PARAM_INPUT_3) && request->hasParam(PARAM_INPUT_5) && request->hasParam(PARAM_INPUT_6) && request->hasParam(PARAM_INPUT_7))
                      {
                          inputMessage1 = request->getParam(PARAM_INPUT_3)->value();
                          inputMessage2 = request->getParam(PARAM_INPUT_5)->value();
                          inputMessage3 = request->getParam(PARAM_INPUT_6)->value();
                          inputMessage4 = request->getParam(PARAM_INPUT_7)->value();

                          if (inputMessage1 == "colorInputStatic")
                          {
                              staticColors.r = inputMessage2.toInt();
                              staticColors.g = inputMessage3.toInt();
                              staticColors.b = inputMessage4.toInt();
                            //   config.fixed_color_r = inputMessage2.toInt();
                            //   config.fixed_color_g = inputMessage3.toInt();
                            //   config.fixed_color_b = inputMessage4.toInt();
                          }
                          if (inputMessage1 == "colorInputGrad1")
                          {
                              config.gradient_color_1_h = inputMessage2.toInt();
                              config.gradient_color_1_s = inputMessage3.toInt();
                              config.gradient_color_1_v = inputMessage4.toInt();
                          }
                          if (inputMessage1 == "colorInputGrad2")
                          {
                              config.gradient_color_2_h = inputMessage2.toInt();
                              config.gradient_color_2_s = inputMessage3.toInt();
                              config.gradient_color_2_v = inputMessage4.toInt();
                          }
                          // http://192.168.1.78/param?id=colored_alarm&r=0&g=50&b=255
                          if (inputMessage1 == "colored_alarm")
                          {
                              led_alarm_active = 2;
                              config.gradient_color_2_h = inputMessage2.toInt();
                              config.gradient_color_2_s = inputMessage3.toInt();
                              config.gradient_color_2_v = inputMessage4.toInt();
                              // led_alarm_blink(inputMessage2.toInt(), inputMessage3.toInt(), inputMessage4.toInt(), 2000, 2000, 5);
                          }
                      }

                      if (request->hasParam(PARAM_INPUT_3) && request->hasParam(PARAM_INPUT_15) && request->hasParam(PARAM_INPUT_16) && request->hasParam(PARAM_INPUT_17) && request->hasParam(PARAM_INPUT_18) && request->hasParam(PARAM_INPUT_19) && request->hasParam(PARAM_INPUT_20))
                      {
                          inputMessage1 = request->getParam(PARAM_INPUT_3)->value();
                          inputMessage2 = request->getParam(PARAM_INPUT_15)->value();
                          inputMessage3 = request->getParam(PARAM_INPUT_16)->value();
                          inputMessage4 = request->getParam(PARAM_INPUT_17)->value();
                          inputMessage5 = request->getParam(PARAM_INPUT_18)->value();
                          inputMessage6 = request->getParam(PARAM_INPUT_19)->value();
                          inputMessage7 = request->getParam(PARAM_INPUT_20)->value();
                      }
                      // http://192.168.1.78/param?id=colored_alarm&r=0&g=50&b=255
                      if (inputMessage1 == "colored_alarm")
                      {
                          led_alarm_active = 2;
                          config.gradient_color_2_h = inputMessage2.toInt();
                          config.gradient_color_2_s = inputMessage3.toInt();
                          config.gradient_color_2_v = inputMessage4.toInt();
                          alarm_onTime = inputMessage5.toInt();
                          alarm_offTime = inputMessage6.toInt();
                          alarm_repeats = inputMessage7.toInt();
                          // led_alarm_blink(inputMessage2.toInt(), inputMessage3.toInt(), inputMessage4.toInt(), 2000, 2000, 5);
                      }

                      request->send(200, "text/plain", "OK");

                      // autosave_ifenabled();
                  });

        server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request)
                  {
                    String inputMessage1;
                    String inputMessage2;
                    String configMessage = "";

                    if (request->hasParam(PARAM_INPUT_12) && request->hasParam(PARAM_INPUT_13))
                    {
                        inputMessage1 = request->getParam(PARAM_INPUT_12)->value();
                        inputMessage2 = request->getParam(PARAM_INPUT_13)->value();
                        configMessage = inputMessage1 + " = " + inputMessage2;
                        configIniParseLine(configMessage.c_str());
                        if (inputMessage1 == "program")
                        {
                            setProgram(inputMessage2.toInt());
                        }
                        if (inputMessage1 == "save_config" && inputMessage2 == "1")
                        {
                            // configIniWriteCurrentConfig();
                            // prefsWriteCurrentWifiConfig();
                            // prefsWriteCurrentProgramConfig();
                        }
                    }

                    if (request->hasParam(PARAM_INPUT_14))
                    {
                        inputMessage1 = request->getParam(PARAM_INPUT_14)->value();

                        configIniParseLine(inputMessage1.c_str());
                    }


                    request->send(200, "text/plain", "OK"); });

        server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request)
                  {
                    request->send(200, "text/plain", "OK");
                    ESP.restart(); });

        server.on(
            "/upload", HTTP_POST, [](AsyncWebServerRequest *request)
            { request->send(200); },
            handleUpload);
    }
    AsyncElegantOTA.begin(&server, OTA_USER, OTA_PASSWORD); // Start ElegantOTA
    server.begin();                                         // Start server
}

// void handleUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final)
// {
//     if (!index)
//     {
//         Serial.printf("UploadStart: %s\n", filename.c_str());
//     }
//     for (size_t i = 0; i < len; i++)
//     {
//         Serial.write(data[i]);
//     }
//     if (final)
//     {
//         Serial.printf("UploadEnd: %s, %u B\n", filename.c_str(), index + len);
//     }
// }

void handleUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final)
{
    String logmessage = "Client:" + request->client()->remoteIP().toString() + " " + request->url();
    Serial.println(logmessage);

    if (!index)
    {
        logmessage = "Upload Start: " + String(filename);
        // open the file on first call and store the file handle in the request object
        request->_tempFile = SPIFFS.open("/" + filename, "w");
        Serial.println(logmessage);
    }

    if (len)
    {
        // stream the incoming chunk to the opened file
        request->_tempFile.write(data, len);
        logmessage = "Writing file: " + String(filename) + " index=" + String(index) + " len=" + String(len);
        Serial.println(logmessage);
    }

    if (final)
    {
        logmessage = "Upload Complete: " + String(filename) + ",size: " + String(index + len);
        // close the file handle as the upload is now done
        request->_tempFile.close();
        Serial.println(logmessage);
        request->redirect("/");

        if (strcmp(filename.c_str(), "config.ini") == 0)
        {
            Serial.println("config.ini detected");
            configIniRead("/config.ini");
            Serial.println("Read config.ini to config struct");
            // prefsWriteCurrentProgramConfig();
            prefs_struct_write();
            Serial.println("wrote current config to nvs pfrefs");
        }
        if (strcmp(filename.c_str(), "wifi.ini") == 0)
        {
            Serial.println("wifi.ini detected");
            configIniRead("/wifi.ini");
            Serial.println("Read wifi.ini to config struct");
            prefsWriteCurrentWifiConfig();
            Serial.println("wrote current wifi credentials to nvs pfrefs");
            Serial.println("Disconnect from WiFi and reconnect with new credentials");
            WiFi.disconnect();
            setupWifi();
        }
    }
}