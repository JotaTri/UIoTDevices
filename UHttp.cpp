#include "UHttp.h"

UHttp::UHttp(String server){
  this->device_identificator();

  this->server = server;
  WiFi.begin("Trojan 2.0", "Ologineasenh4!");
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    Serial.println("Connecting to Wifi");
    delay(2500);
 }
 Serial.println("Connection Successfull");
}


bool UHttp::register_device(){
  char *data;
  data = this->make_client_data();
  this->http.begin(this->server + "/Device");
  this->http.addHeader("Content-Type", "application/json");
  this->http.POST(data);
  // data = "oicara{'tudo': 1}";
  // this->publish("Register/Device", data);
  return false;
}
bool UHttp::register_service(Service){
  return false;
}
bool UHttp::register_data(char *data){
  return false;
}
