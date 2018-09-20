#include "UHttp.h"

UHttp::UHttp(){}


void UHttp::init(){
  this->device_identificator();
}

bool UHttp::register_device(){
  char *data = NULL;
  data = this->make_client_data(data);
  // Serial.println(strlen(data));
  bool result = this->send("client", data);
  for(int i = 0; i < strlen(data); i++)
    data[i] = '\0';
  free(data);
  data = NULL;
  return result;
}

bool UHttp::register_service(Service s){
  char *data = NULL;
  data = this->make_service_data(s, data);

  bool result = this->send("service", data);
  free(data);
  data = NULL;
  return result;
}

bool UHttp::register_data(Service s, char* value, int sensitive){
  char *data = NULL;
  data = this->make_raw_data(s, value, sensitive, data);

  bool result = this->send("data", data);
  free(data);
  data = NULL;
  return result;
}

bool UHttp::send(const char* DIE, char* send_data){
  Serial.pritln(DIE);
  Serial.println(send_data);
  while(!Serial.available());
  if(Serial.readString() == 1){
    return true;
  }
  else{
    return false;
  }

}
