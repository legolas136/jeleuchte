#include "my_mqtt.h"

// IPAddress mqttServer(192, 168, 1, 112);

WiFiClient espClient;

PubSubClient mqttclient(espClient);

MqttConfig mqttConfig;

void setupMqtt()
{
    Serial.println("MqttConfig");
    // Serveradresse
    strcpy(mqttConfig.user, MQTT_USER);
    strcpy(mqttConfig.password, MQTT_PASSWORD);
    strcpy(mqttConfig.id, getChipID().c_str());
    strcpy(mqttConfig.room, "wz");
    mqttConfig.server_ip.fromString(MQTT_SERVER_IP);
    mqttConfig.server_port = MQTT_SERVER_PORT;
    mqttclient.setServer(mqttConfig.server_ip, mqttConfig.server_port);
    // Callbackfunktion bei ankommender Nachricht
    mqttclient.setCallback(mqttcallback);

    mqtt_reconnect();
}

void mqtt_reconnect(uint16_t mqtt_reconnect_interval)
{
    static unsigned long lastmillis = millis();
    // Loop until we're reconnected
    if ((millis() - lastmillis > mqtt_reconnect_interval) && !mqttclient.connected())
    {
        lastmillis = millis();

        Serial.print("Attempting MQTT connection to Server: ");
        Serial.print(mqttConfig.server_ip.toString());
        Serial.print(":");
        Serial.print(mqttConfig.server_port);
        Serial.print(". ClientID=");
        Serial.print(mqttConfig.id);
        Serial.print(". User=");
        Serial.print(mqttConfig.user);
        Serial.print(". Password=");
        Serial.print(mqttConfig.password);
        Serial.print(" ... ");
        // Attempt to connect
        if (mqttclient.connect(mqttConfig.id, mqttConfig.user, mqttConfig.password))
        {
            Serial.println("success!");
            // Once connected, publish an announcement...
            mqttclient.publish(MQTT_TOPIC "/status", "connected");
            // ... and resubscribe
            mqtt_subsriptions();
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(mqttclient.state());
            Serial.println(" trying again after a while");
        }
    }
}

void mqtt_subsriptions()
{

    Serial.print("MQTT: subscribig to topic:");
    Serial.println(mqtt_built_topic("#").c_str());
    Serial.println(mqtt_built_topic("#", true).c_str());

    // Subscribe to device specific set cmds
    mqttclient.subscribe(mqtt_built_topic("#").c_str());
    // Subscribe to room specific set cmds
    mqttclient.subscribe(mqtt_built_topic("#", true).c_str());

    // mqttclient.subscribe(MQTT_TOPIC "/power");
    // mqttclient.subscribe(TOPIC "/power");
    // mqttclient.subscribe(TOPIC "/power");
}

void mqttcallback(char *topic, byte *payload, unsigned int length)
{
    // Serial.println("callback executed");
    char *payload_cstring = (char *)payload;
    payload_cstring[length] = '\0';

    int payload_int = atoi(payload_cstring);

    if (true) // device specific
    {
        if (strcmp(topic, mqtt_built_topic("set/power_switch").c_str()) == 0)
        {
            if (payload_int == 1)
            {
                power_switch = true;
            }
            if (payload_int == 0)
            {
                ledsOff();
            }
        }
        if (strcmp(topic, mqtt_built_topic("set/led/static_color_r").c_str()) == 0)
        {
            config.fixed_color_r = uint8_t(payload_int);
        }
        if (strcmp(topic, mqtt_built_topic("set/led/static_color_g").c_str()) == 0)
        {
            config.fixed_color_g = uint8_t(payload_int);
        }
        if (strcmp(topic, mqtt_built_topic("set/led/static_color_b").c_str()) == 0)
        {
            config.fixed_color_b = uint8_t(payload_int);
        }
        if (strcmp(topic, mqtt_built_topic("set/led/brightness").c_str()) == 0)
        {
            config.brightness = uint8_t(payload_int);
        }
        if (strcmp(topic, mqtt_built_topic("set/led/program").c_str()) == 0)
        {
            config.program = payload_int;
        }
    }

    if (true) // room specific
    {
        if (strcmp(topic, mqtt_built_topic("set/power_switch", true).c_str()) == 0)
        {
            if (payload_int == 1)
            {
                power_switch = true;
            }
            if (payload_int == 0)
            {
                ledsOff();
            }
        }
        if (strcmp(topic, mqtt_built_topic("set/led/program", true).c_str()) == 0)
        {
            config.program = uint8_t(payload_int);
        }
        if (strcmp(topic, mqtt_built_topic("set/led/brightness", true).c_str()) == 0)
        {
            config.global_brightness = uint8_t(payload_int);
        }
        if (strcmp(topic, mqtt_built_topic("set/led/static_color_r", true).c_str()) == 0)
        {
            config.fixed_color_r = uint8_t(payload_int);
        }
        if (strcmp(topic, mqtt_built_topic("set/led/static_color_g", true).c_str()) == 0)
        {
            config.fixed_color_g = uint8_t(payload_int);
        }
        if (strcmp(topic, mqtt_built_topic("set/led/static_color_b", true).c_str()) == 0)
        {
            config.fixed_color_b = uint8_t(payload_int);
        }
    }
}

void mqttPublish(const char *topic, const char *msg)
{
    Serial.print("MQTT: \n Topic: ");
    Serial.print(topic);
    Serial.print("Payload: ");
    Serial.print(msg);
    Serial.print(" ... ");
    if (mqttclient.publish(topic, msg))
    {
        Serial.println(" success!");
    }
    else
    {
        Serial.println(" failed!");
    }
}

void send_mqtt_data(unsigned long interval)
{
    // char buf[2];
    // itoa(int(power_switch), buf, 10);

    static unsigned long lastmillis = millis();
    if (millis() - lastmillis >= interval)
    {
        lastmillis = millis();
        // mqttclient.publish(MQTT_TOPIC "/state", buf);
        // mqttclient.publish(MQTT_TOPIC "/led/program", buf);
        // mqttclient.publish(MQTT_TOPIC "/power_switch", String(power_switch).c_str());

        mqttclient.publish(mqtt_built_topic("power_switch", false).c_str(), String(power_switch).c_str());
        mqttclient.publish(mqtt_built_topic("millis", false).c_str(), String(millis()).c_str());

        mqttclient.publish(mqtt_built_topic("led/static_color_r", false).c_str(), String(config.fixed_color_r).c_str());
        mqttclient.publish(mqtt_built_topic("led/static_color_g", false).c_str(), String(config.fixed_color_g).c_str());
        mqttclient.publish(mqtt_built_topic("led/static_color_b", false).c_str(), String(config.fixed_color_b).c_str());

        // Serial.println("Sent MQTT Update");
        // mqttclient.publish(MQTT_TOPIC "/BassNewValue", String(Bass.getOutput()).c_str());
        // mqttclient.publish(MQTT_TOPIC "/BassOldValue", String(Bass.getInput()).c_str());
        // mqttclient.publish(MQTT_TOPIC "/BassIncrementor", String(Bass.incrementor).c_str());
        // mqttclient.publish(MQTT_TOPIC "/BassReductor", String(Bass.reductor).c_str());
        // mqttclient.publish(MQTT_TOPIC "/BassReductor", String(Bass.reductor).c_str());

        // mqttclient.publish(topic_pre, String(config.fixed_color_r).c_str());
        // mqttclient.publish(topic_pre, String(config.fixed_color_g).c_str());
        // mqttclient.publish(topic_pre, String(config.fixed_color_b).c_str());
    }
}

void mqttTick()
{

    if (mqttclient.connected())
    {
        try
        {
            send_mqtt_data(1000);
        }
        catch(const std::exception& e)
        {
            Serial.println(e.what());
        }
        
        
    }
    else
    {
        mqtt_reconnect();
    }
    mqttclient.loop();
}

String mqtt_built_topic(const char *trailing_topic, bool is_room)
{
    String topic_str;

    topic_str += mqttConfig.room;
    topic_str += "/";
    topic_str += "esp32";
    topic_str += "/";
    if (!is_room)
    {
        topic_str += mqttConfig.id;
        topic_str += "/";
    }

    topic_str += trailing_topic;

    return topic_str;
}