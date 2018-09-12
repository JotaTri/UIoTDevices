#ifndef UHTTP_H
#define UHTTP_H

#ifndef HTTP_PORT
#define HTTP_PORT  8000
#endif

#include <ArduinoJson.h>
#include <Ethernet.h>
#include "BaseProtocol.h"

class UHttp : public BaseProtocol{
    public:
        UHttp();
        UHttp(const char*);
        void init();
        void set_server(const char*);
        bool register_device();
        bool register_service(Service);
        bool register_data(Service, char*, int);
        bool POST(const char*, char*);

    private:
        const char* server;
    public:
        EthernetClient eth_client;



};





#endif
