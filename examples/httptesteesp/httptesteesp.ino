#include <UHttp.h>


UHttp cliente;
Service service1;

void setup(){
  Serial.begin(9600);
  while (!Serial);
  delay(1000);
  cliente.init();
  cliente.set_server("192.168.0.109");
  service1 = cliente.create_service(1, "getTemp", "*C", 1, "Temperatura");
  //cliente.send_data(service1, (char*)"56", 0);

}

void loop(){
  cliente.send_data(service1, (char*)"56", 0);
  delay(5000);
  Serial.println("loop");

}
