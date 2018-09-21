#ifndef USerial_H
#define USerial_H

#ifndef HTTP_PORT
#define HTTP_PORT  8000
#endif

#include <ArduinoJson.h>
#include "BaseProtocol.h"

class USerial : public BaseProtocol{
    public:
        USerial();
        USerial(const char*);
        void init();
        bool register_device();
        bool register_service(Service);
        bool register_data(Service, char*, int);
        bool send(const char*, char*);

    private:
        const char* server;
};





#endif
