#ifndef BASEPROTOCOL_H
#define BASEPROTOCOL_H


#include <PubSubClient.h>
#include <EEPROM.h>
#include <ArduinoJson.h>

class Service {
  public:
    Service (int number, const char *name, String unit, bool numeric, String parameter){
      this->number = number;
      this->name = name;
      this->unit = unit;
      this->numeric = numeric;
      this->parameter = parameter;
    }
    int number;
    const char * name;
    String *tags;
    String unit = "";
    bool numeric;
    String parameter = "";
  };


class BaseProtocol {
    public:
        bool send_data();
        bool register_all(Service, char*);
        virtual bool register_device() = 0;
        virtual bool register_service(Service)= 0;
        virtual bool register_data(char *data)= 0;
        bool send_data(Service , char*);
        void device_identificator();
        Service create_service(int , const char *, String, bool, String);
        char nibble_to_char(int);
        char *make_client_data();
        char *make_service_data(Service);
        char *make_raw_data(Service, char*);

    private:
        bool DEVICE_REGISTERED = false;

    protected:
        byte mac_byte[6] = {0x9A, 'I', 'O', 'T', 0, 0};
        byte chipset_byte[6];
        String name = "Arduino Uno";
        String serial = "C210";
        String processor = "Arduino Processor";
        String channel = "Ethernet";
        String chipset = "";
        String mac = "";
};

#endif
