#include <USerial.h>
#include "DHT.h"


#define light_sensor_pin 7


USerial device;
Service service1;

DHT dht(5, DHT11);
 Service  temp_service;
  Service  hum_service;
  Service  lum_service;
void setup(){
  Serial.begin(9600);
  while (!Serial);
  delay(1000);

  pinMode(light_sensor_pin, INPUT);      // sets the digital pin 13 as output

  device.init();
  temp_service = device.create_service(1, "getTemp", "*C", 1, "Temperature");
  hum_service = device.create_service(2, "getHum", "g/m^3(H20)/g/m^3(air)", 1, "Hummidity");
  lum_service = device.create_service(3, "getLum", "bool", 0, "Luminosity");

  dht.begin();
}

void loop(){
  delay(2000);
  float h = dht.readHumidity();
  delay(2000);
  float t = dht.readTemperature();
  if(!digitalRead(light_sensor_pin)){
    device.send_data(lum_service,"true",0);
    Serial.println("Tem Luz");
  }
//  else{
//    Serial.println("Não Tem Luz");
//  }
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h)){
    Serial.println("Failed to read from DHT");
  }
  else
  {
//    Serial.print("Umidade: ");
//    Serial.print(h);
//    Serial.print(" %");
    device.send_data(hum_service,String(h).c_str(),0);


//    Serial.print("Temperatura: ");
//    Serial.print(t);
//    Serial.println(" *C");
    device.send_data(temp_service,String(t).c_str(),0);

  }


}
