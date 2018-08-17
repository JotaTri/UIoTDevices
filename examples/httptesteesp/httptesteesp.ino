#include <UHttp.h>

void setup(){
  Serial.begin(9600);
  while (!Serial);
  delay(1000);

  
  UHttp cliente("http://192.168.0.109");
  Service service1 = cliente.create_service(1, "getTemp", "°C", true, "Temperatura");
  cliente.send_data(service1, (char*)"56", 0);
}

void loop(){
  delay(5000);
  Serial.println("loop");
}
