#include "UZigBee.h"

UZigBee::UZigBee(){}


UZigBee::UZigBee(const char *server){
  this->device_identificator();

  this->server = server;
  // Ethernet.begin(this->mac_byte);

}

void UZigBee::init(){
  this->device_identificator();
  this->xbee = XBee();
  this->Broadcast = XBeeAddress64(0x0013a200 ,0x40c8b326);
}


void UZigBee::set_server(const char *server){
  this->server = server;
}

bool UZigBee::register_device(){
  char *data = NULL;
  data = this->make_client_data(data);
  XBeeAddress64 Broadcast = XBeeAddress64(0x0013a200 ,0x40c8b326);
  ZBTxRequest zbtx_1 = ZBTxRequest(Broadcast , (char*)data, strlen(data));
  xbee.send(zbtx_1);

  for(int i = 0; i < strlen(data); i++)
    data[i] = '\0';
  free(data);
  data = NULL;
  bool result = true;
  return result;
}

bool UZigBee::register_service(int s){
  char *data = NULL;
  data = this->make_service_data(this->service[s], data);
  XBeeAddress64 Broadcast = XBeeAddress64(0x0013a200 ,0x40c8b326);
  ZBTxRequest zbtx_1 = ZBTxRequest(Broadcast , (char*)data, strlen(data));
  xbee.send(zbtx_1);
  for(int i = 0; i < strlen(data); i++)
    data[i] = '\0';
  free(data);
  data = NULL;
  bool result = true;
  return result;
}

bool UZigBee::register_data(int s, char* value, int sensitive){
  char *data = NULL;
  data = this->make_raw_data(this->service[s], value, sensitive, data);
  XBeeAddress64 Broadcast = XBeeAddress64(0x0013a200 ,0x40c8b326);
  ZBTxRequest zbtx_1 = ZBTxRequest(Broadcast , (char*)data, strlen(data));
  xbee.send(zbtx_1);
  for(int i = 0; i < strlen(data); i++)
    data[i] = '\0';
  free(data);
  data = NULL;
  bool result = true;
  return result;
}
