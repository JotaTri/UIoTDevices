#include "USerial.h"

USerial::USerial(){}


void USerial::init(){
  this->device_identificator();
  while(true){
    while(!Serial.available());
    if(Serial.readString() == "*WM: freeing allocated params!"){
      break;
    }
  }
}

bool USerial::register_device(){
  char *data = NULL;
  data = this->make_client_data(data);
  bool result = this->send("client", data);
  for(int i = 0; i < strlen(data); i++)
    data[i] = '\0';
  free(data);
  data = NULL;
  return result;
}

bool USerial::register_service(Service s){
  char *data = NULL;
  data = this->make_service_data(s, data);

  bool result = this->send("service", data);
  free(data);
  data = NULL;
  return result;
}

bool USerial::register_data(Service s, char* value, int sensitive){
  char *data = NULL;
  data = this->make_raw_data(s, value, sensitive, data);

  bool result = this->send("data", data);
  free(data);
  data = NULL;
  return result;
}

bool USerial::send(const char* DIE, char* send_data){
  Serial.println(DIE);
  delay(1000);
  Serial.println(send_data);
  while(!Serial.available());
  String p = Serial.readString();
  if( p == "1"){
    Serial.println("1");
    return true;
  }
  else{
    Serial.println("0");
    return false;
  }

}
