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
  this->mac_byte[4] = bytes[0];
  this->mac_byte[5] = bytes[1];

  for (int i = 0; i < 6; i++){
    this->chipset_byte[i] = bytes[i+2];
  }

  for(int i = 0; i < 6; i++){
    byte b = this->chipset_byte[i];
    this->chipset += "0x";
    this->chipset += this->nibble_to_char((b & 0xF0)>>4);
    this->chipset += this->nibble_to_char(b & 0xF);
    this->chipset += " ";
  }

  for(int i = 0; i < 6; i++){
    byte b = this->mac_byte[i];
    this->mac += "0x";
    this->mac += this->nibble_to_char((b & 0xF0)>>4);
    this->mac += this->nibble_to_char(b & 0xF);
    this->mac += " ";
  }
  Serial.print("MAC: ");
  Serial.println(this->mac);
  // for (int i = 0; i< 6; i++){
  //   Serial.print(this->mac[i]);
  //   Serial.print(", ");
  // }

  Serial.print("CHIPSET: ");
  Serial.println(this->chipset);
  // for (int i = 0; i< 6; i++){
  //   Serial.print(this->chipset[i]);
  //   Serial.print(", ");
  // }

  // Serial.println("");

}

Service BaseProtocol::create_service(int number, const char *name, String unit, bool numeric, String parameter){
  return Service(number, name, unit, numeric, parameter);
}

bool BaseProtocol::register_all(Service service, char *data){
	this->register_device();
  this->register_service(service);
	return false;
	//return this->register_device() && this->register_service(service) && this->register_data(data);
}

char *BaseProtocol::make_client_data(){
  Serial.println("Registering Device");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  // Serial.print("Name: ");
  // Serial.println(this->name);
  // Serial.print("Chipset: ");
  // Serial.println(this->chipset);
  // Serial.print("Mac: ");
  // Serial.println(this->mac);
  // Serial.print("serial: ");
  // Serial.println(this->serial);
  // Serial.print("Processor: ");
  // Serial.println(this->processor);
  // Serial.print("Channel: ");
  // Serial.println(this->channel);

  String p;
  root["name"] = this->name.c_str();
  root["chipset"] = this->chipset;
  root["mac"] = this->mac;
  root["serial"] = this->serial.c_str();
  root["processor"] = this->processor;
  root["channel"] = this->channel;
  char *c = new char[root.measureLength() + 1];
  root.printTo((char*)c, root.measureLength() + 1);
  Serial.println("auiiiiii");
  Serial.println(c);
  Serial.println("qqqqqqq");
  return (c);
}


char *BaseProtocol::make_service_data(Service service){
  Serial.println("Registering Service");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  // root["number"] = service.number;
  root["chipset"] = this->chipset;
  root["mac"] = this->mac;
  root["name"] = service.name;
  root["parameter"] = service.parameter;
  root["unit"] = service.unit;
  // root["numeric"] = service.numeric;

  char *c = new char[root.measureLength() + 1];
  root.printTo((char*)c, root.measureLength() + 1);
  return(c);
}

char *BaseProtocol::make_raw_data(Service s, char *data){
  return (char*)"asdf";
}

char BaseProtocol::nibble_to_char(int nibble){
  return nibble + 48 + 7*(nibble > 9);
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
