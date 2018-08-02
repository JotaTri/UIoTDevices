#ifndef UHTTP_H
#define UHTTP_H

#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include "BaseProtocol.h"
#include <ESP8266WiFi.h>

class UHttp : public BaseProtocol{
    public:
        UHttp(String);
        bool register_device();
        bool register_service(Service);
        bool register_data(char *data);
        // char* add_mac_chipset(char *data);
        // char *json_to_char(JsonObject&);
        // bool publish(const char[], char*);

    private:
        // PubSubClient mqtt_client;
        String server;
        HTTPClient http;
        int mqtt_port = 1883;


};





#endif
