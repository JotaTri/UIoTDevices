#ifndef UZIGBEE_H
#define UZIGBEE_H


#include <XBee.h>
#include "BaseProtocol.h"

class UZigBee : public BaseProtocol{
    public:
        UZigBee();
        UZigBee(const char*);
        void init();
        void set_server(const char*);
        bool register_device();
        bool register_service(int);
        bool register_data(int, char*, int);
        bool POST(const char*, char*);

    private:
        const char* server;
        XBee xbee;
        XBeeAddress64 Broadcast;

};

#endif
