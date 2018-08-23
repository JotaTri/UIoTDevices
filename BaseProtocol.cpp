#include "BaseProtocol.h"

Service BaseProtocol::create_service(int number, const char *name, String unit, bool numeric, String parameter){
  return Service(number, name, unit, numeric, parameter);
}

bool BaseProtocol::send_data(Service service, float *data, int array_size, int sensitive=0) {
  char * char_data = float_to_char(data, array_size);
	this->DEVICE_REGISTERED = (!this->DEVICE_REGISTERED)? this->register_all(service, char_data, sensitive) : this->register_data(service, char_data, sensitive);
  free(char_data);
  return this->DEVICE_REGISTERED;
}

void BaseProtocol::device_identificator(){
  int address = 0;
  int bytes[8];
  
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
  // Serial.print("MAC: ");
  // Serial.println(this->mac);
  //
  // Serial.print("CHIPSET: ");
  // Serial.println(this->chipset);

}

bool BaseProtocol::register_all(Service service, char *data, int sensitive){
	return this->register_device() && this->register_service(service) && this->register_data(service, data, sensitive);
}


char *BaseProtocol::make_client_data(char* json){
  Serial.println("Registering Device");

  Serial.println(strlen(json));
  json = (char*)malloc(2*sizeof(char));
  json[0] = '{';
  json[1] = '\0';
  json = this->append_json(json, "name", this->name.c_str());
  json = this->append_json(json, "chipset", this->chipset.c_str());
  json = this->append_json(json, "mac", this->mac.c_str());
  json = this->append_json(json, "serial", this->serial.c_str());
  json = this->append_json(json, "processor", this->processor.c_str());
  json = this->append_json(json, "channel", this->channel.c_str());
  json[strlen(json)-1] = '}';
  Serial.println(json);
  return json;
}


char *BaseProtocol::make_service_data(Service service, char* json){
  Serial.println("Registering Service");

  Serial.println(strlen(json));
  json = (char*)malloc(2*sizeof(char));
  json[0] = '{';
  json[1] = '\0';
  json  = this->append_json(json, "name", service.name);
  json = this->append_json(json, "chipset", this->chipset.c_str());
  json = this->append_json(json, "mac", this->mac.c_str());
  json = this->append_json(json, "parameter", service.parameter.c_str());
  json = this->append_json(json, "number", String(service.number).c_str());
  json = this->append_json(json, "unit", service.unit.c_str());
  json = this->append_json(json, "numeric", String(service.numeric).c_str());
  json[strlen(json)-1] = '}';
  Serial.println(json);
  return json;
}

char *BaseProtocol::make_raw_data(Service s, char *data, int sensitive, char* json){
  Serial.println("Raw Data");
  Serial.println(strlen(json));
  json = (char*)malloc(2*sizeof(char));
  json[0] = '{';
  json[1] = '\0';
  json = this->append_json(json, "chipset", this->chipset.c_str());
  json = this->append_json(json, "mac", this->mac.c_str());
  json = this->append_json(json, "sensitive", String(sensitive).c_str());
  json = this->append_json(json, "serviceNumber", String(s.number).c_str());
  json = this->append_json(json, "values", data);
  json[strlen(json)-1] = '}';
  Serial.println(json);
  return json;
}


char* BaseProtocol::append_json(char *json, const char* key, const char* value){
  Serial.println(strlen(json));
  json = (char*) realloc (json, (strlen(key) + strlen(value) + 7 + strlen(json)) * sizeof(char)); // 6 because "" and : and ,
  strcat(json, "\"");
  strcat(json, key);
  strcat(json, "\":\"");
  strcat(json, value);
  strcat(json, "\",");
  json[strlen(json)] = '\0';
  return json;
}

char* BaseProtocol::float_to_char(float* float_array, int array_size){
  char *values;
  values = (char*)malloc(2*sizeof(char));
  values[0] = '[';
  values[1] = '\0';
  String b;
  int contador = 2;
  for(int i = 0; i < array_size; i++){
    // Serial.println(dtostrf(float_array[i], 10, 3, b));
    b = String(float_array[i]);
    contador += b.length() + 1;
    // Serial.print("b:");
    // Serial.println(b);
    // Serial.print("contador: ");
    // Serial.println(contador);
    // Serial.print("values: ");
    // Serial.println(values);
    values = (char*) realloc (values, (contador) * sizeof(char));
    strcat(values, b.c_str());
    strcat(values, ",");
    // Serial.print("values: ");
    // Serial.println(values);
  }
  values[contador-2] = '\0';

  strcat(values, "]");
  // Serial.print("values: ");
  // Serial.println(values);
  // cout << values;

  return values;
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
