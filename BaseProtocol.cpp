#include "BaseProtocol.h"

bool BaseProtocol::send_data(Service service, char *data, int sensitive=0) {
  // Serial.println("Send Data");
  // this->register_device();
	(!this->DEVICE_REGISTERED)? this->register_all(service, data, sensitive) : this->register_data(service, data, sensitive);
  this->DEVICE_REGISTERED = true;
}

void BaseProtocol::device_identificator(){
  int address = 0;
  int bytes[8];
  Serial.println(EEPROM.read(0));
  Serial.println(EEPROM.read(1));
  if (EEPROM.read(0) != 'U' || EEPROM.read(1) != 'T'){
    EEPROM.write(0, 'U');
    EEPROM.write(1, 'T');

    int iterator = 0xFF;
    for (int i = 0; i < 8; i++){
      int a = millis();
      int b = rand() % 123 + 1;
      int unique = a * b;
      bytes[i] = unique & iterator;
      EEPROM.write(i + 2,bytes[i]);
    }
  } else{
    for (int i = 0; i < 8; i++){
      bytes[i] = EEPROM.read(i+2);
   }
  }
  this->mac_byte[4] = bytes[0];
  this->mac_byte[5] = bytes[1];

  for (int i = 0; i < 6; i++){
    this->chipset_byte[i] = bytes[i+2];
  }

  for(int i = 0; i < 6; i++){
    byte b = this->chipset_byte[i];
    this->chipset += this->nibble_to_char((b & 0xF0)>>4);
    this->chipset += this->nibble_to_char(b & 0xF);
    this->chipset += ":";
  }
  this->chipset.remove(this->chipset.length()-1,1);

  for(int i = 0; i < 6; i++){
    byte b = this->mac_byte[i];
    this->mac += this->nibble_to_char((b & 0xF0)>>4);
    this->mac += this->nibble_to_char(b & 0xF);
    this->mac += ":";
  }
  this->mac.remove(this->mac.length()-1,1);
  Serial.print("MAC: ");
  Serial.println(this->mac);

  Serial.print("CHIPSET: ");
  Serial.println(this->chipset);

}

Service BaseProtocol::create_service(int number, const char *name, String unit, bool numeric, String parameter){
  return Service(number, name, unit, numeric, parameter);
}

bool BaseProtocol::register_all(Service service, char *data, int sensitive){
	return this->register_device() && this->register_service(service) && this->register_data(service, data, sensitive);
}

char *BaseProtocol::make_client_data(){
  // Serial.println("Registering Device");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  String p;
  root["name"] = (char*)this->name.c_str();
  root["chipset"] = this->chipset;
  root["mac"] = this->mac;
  root["serial"] = (char*)this->serial.c_str();
  root["processor"] = this->processor;
  root["channel"] = this->channel;

  char *c = new char[root.measureLength() + 1];
  root.printTo(c, root.measureLength() + 1);
  return (c);
}


char *BaseProtocol::make_service_data(Service service){
  Serial.println("Registering Service");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["number"] = service.number;
  root["chipset"] = this->chipset;
  root["mac"] = this->mac;
  root["name"] = service.name;
  root["parameter"] = service.parameter;
  root["unit"] = service.unit;
  root["numeric"] = service.numeric;

  char *c = new char[root.measureLength() + 1];
  root.printTo((char*)c, root.measureLength() + 1);
  return(c);
}

char *BaseProtocol::make_raw_data(Service s, char *data, int sensitive){
  Serial.println("Raw Data");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["chipset"] = this->chipset;
  root["mac"] = this->mac;
  root["sensitive"] = sensitive;
  root["serviceNumber"] = s.number;
  root["values"] = data;

  char *c = new char[root.measureLength() + 1];
  root.printTo((char*)c, root.measureLength() + 1);
  return(c);
}

char BaseProtocol::nibble_to_char(int nibble){
  return nibble + 48 + 7*(nibble > 9); //ascii based
}

bool BaseProtocol::register_service(Service service){
  return false;
}
bool BaseProtocol::register_device(){
  return false;
}
bool BaseProtocol::register_data(Service svc, char* dt, int stv){
  return false;
}
