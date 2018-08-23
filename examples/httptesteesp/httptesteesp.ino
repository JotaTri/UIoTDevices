#include <UHttp.h>


UHttp cliente;
Service service1;

void setup(){
  Serial.begin(9600);
  while (!Serial);
  delay(1000);
  cliente.init();
  cliente.set_server("172.16.9.69");
  service1 = cliente.create_service(1, "getTemp", "*C", 1, "Temperatura");
  //cliente.send_data(service1, (char*)"[56]", 0);

}

void loop(){
  float ar[] = {1.0,2.0,3.0,4.0,5.0,6.9};
  cliente.send_data(service1, ar , 6, 0);
  delay(5000);
  Serial.println("loop");

}
