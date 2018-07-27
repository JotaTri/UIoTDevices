#include "BaseProtocol.h"

bool BaseProtocol::send_data(Service service,char *data) {
  Serial.println("Send Data");
	(!this->DEVICE_REGISTERED)? this->register_all(service, data) : this->register_data(data);
}

void BaseProtocol::device_identificator(){
  int address = 0;
  int bytes[8];
  Serial.println(EEPROM.read(0));
  Serial.println(EEPROM.read(1));
  if (EEPROM.read(0) != 74 || EEPROM.read(1) != 114){
    Serial.println("aquiii");
    EEPROM.write(0, 74);
    EEPROM.write(1, 114);

    int iterator = 0xFF;
    for (int i = 0; i < 8; i++){
      int a = millis();
      int b = rand() % 123 + 1;
      Serial.print("millis=");
      Serial.println(a);
      Serial.print("rand=");
      Serial.println(b);
      int unique = a * b;
      Serial.print("Unique=");
      Serial.println(unique);
      bytes[i] = unique & iterator;
      Serial.print("bytes[");
      Serial.print(i);
      Serial.print("]=");
      Serial.println(bytes[i]);
      EEPROM.write(i + 2,bytes[i]);
      //unique = unique >> 8;
    }
  } else{
    for (int i = 0; i < 8; i++){
      bytes[i] = EEPROM.read(i+2);
//      Serial.print("bytes[");
//      Serial.print(i);
//      Serial.print("]=");
//      Serial.println(bytes[i]);
   }
  }
  this->mac[4] = bytes[0];
  this->mac[5] = bytes[1];
  for (int i = 0; i < 6; i++){
    this->chipset[i] = bytes[i+2];
  }

  Serial.print("MAC: ");
  for (int i = 0; i< 6; i++){
    Serial.print(this->mac[i]);
    Serial.print(", ");
  }
  Serial.println("");
  Serial.print("CHIPSET: ");
  for (int i = 0; i< 6; i++){
    Serial.print(this->chipset[i]);
    Serial.print(", ");
  }

  Serial.println("");

}

Service BaseProtocol::create_service(int number, const char *name){
  return Service(number, name);
}

bool BaseProtocol::register_all(Service service, char *data){
	this->register_device();
	return false;
	//return this->register_device() && this->register_service(service) && this->register_data(data);
}

bool BaseProtocol::register_service(Service service){
  return false;
}
bool BaseProtocol::register_device(){
  return false;
}
bool BaseProtocol::register_data(char* data){
  return false;
}

