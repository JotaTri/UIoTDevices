#ifndef UMQTT_H
#define UMQTT_H
#define MQTT_MAX_PACKET_SIZE 140


#include <PubSubClient.h>
#include "BaseProtocol.h"
#include <ArduinoJson.h>
#include <SPI.h>
#include <Ethernet.h>

class UMqtt : public BaseProtocol{
    public:
        UMqtt(Client&, IPAddress);
        bool register_device();
        bool register_service(Service);
        bool register_data(Service, char*, int);
        char* add_mac_chipset(char *data);
        char *json_to_char(JsonObject&);
        bool publish(const char[], char*);

    private:
        PubSubClient mqtt_client;
        int mqtt_port = 1883;


};

#endif
