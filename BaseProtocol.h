#ifndef BASEPROTOCOL_H
#define BASEPROTOCOL_H

#include <PubSubClient.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <Ethernet.h>

class Service {
  public:
    Service (int number, const char *name, String unit, int numeric, String parameter){
      this->number = number;
      this->name = name;
      this->unit = unit;
      this->numeric = numeric;
      this->parameter = parameter;
    }
    Service(){}
    int number;
    const char * name;
    String *tags;
    String unit = "";
    int numeric;
    String parameter = "";
  };


class BaseProtocol {
    public:
        bool send_data();
        bool register_all(Service, char*, int);
        void device_identificator();
        virtual bool register_device() = 0;
        virtual bool register_service(Service)= 0;
        virtual bool register_data(Service, char*, int)= 0;
        // void init();
        bool send_data(Service , char*, int);
        Service create_service(int , const char *, String, bool, String);
        char nibble_to_char(int);
        char *make_client_data(char*);
        char *make_service_data(Service, char*);
        char *make_raw_data(Service, char*, int, char*);
        char *append_json(char*, const char*, const char*);
    private:
        bool DEVICE_REGISTERED = false;

    protected:
        byte mac_byte[6] = {0x9A, 'I', 'O', 'T', 0, 0};
        byte chipset_byte[6];
        String name = "A";
        String serial = "C";
        String processor = "AP";
        String channel = "E";
        String chipset = "";
        String mac = "";
};

#endif
