#include "UMqtt.h"

UMqtt::UMqtt(Client& client, IPAddress server) {
  this->device_identificator();

//  Serial.println("Getting IP Address");
//  Ethernet.begin(this->mac);
//  //byte m[] = { 0x9A, 'I', 'O', 'T', 0xFB, 0x06 };
//  //Ethernet.begin(m);
//  Serial.print ("My IP address: ");
//  for (byte thisByte = 0; thisByte < 4; thisByte++) {
//    // print the value of each byte of the IP address:
//    Serial.print (Ethernet.localIP ()[thisByte], DEC);
//    Serial.print (".");
//  }
//
//  Serial.println ();
  
  delay (1000);
  
	this->mqtt_client.setClient(client);
  this->mqtt_client.setServer(server, this->mqtt_port);
}

bool UMqtt::register_device(){
  Serial.println("Registering Device");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  Serial.print("Name: ");
  Serial.println(this->name);
  Serial.print("Chipset: ");
  Serial.println(this->chipset[0]);
  Serial.print("Mac: ");
  Serial.println(this->mac[0]);
  Serial.print("serial: ");
  Serial.println(this->serial);
  Serial.print("Processor: ");
  Serial.println(this->processor);
  Serial.print("Channel: ");
  Serial.println(this->channel);
  
  String p;
  root["name"] = this->name.c_str();
//  root.prettyPrintTo(p);
//  Serial.println(p);
  root["chipset"] = this->chipset;
  root["mac"] = this->mac;
  root["serial"] = this->serial.c_str();
  root["processor"] = this->processor;
  root["channel"] = this->channel;
  root.printTo(p);
  Serial.println(p);
  char *c = new char[p.length() + 1];
  Serial.print("Size: ");
  Serial.println(p.length() + 1);
  strcpy(c, p.c_str());
  Serial.println(c);
//  root.printTo((char*)c, root.measureLength() + 1);
//  Serial.println(c);
  //this->json_to_char(root);
  //Serial.println(this->json_to_char(root));
//  return this->publish("Register/Device", this->json_to_char(root));
  return false;
}


bool UMqtt::register_service(Service service){
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["tags"] = service.tags;
  root["number"] = service.number;
  root["chipset"] = this->chipset;
  root["mac"] = this->mac;
  root["name"] = service.name;
  root["unit"] = service.unit;
  root["numeric"] = service.numeric;
  
  return this->publish("Register/Service", json_to_char(root));

  return true;
}
bool UMqtt::register_data(char  *data){
	data = this->add_mac_chipset(data);
	return this->publish("Data/", data);
}

bool UMqtt::publish(const char *topic, char *data) {
    Serial.print("Sending Data: ");
    Serial.println(data);
    this->mqtt_client.connect("ClassClient");

    while(!this->mqtt_client.connected()){
      Serial.println("Connecting...");
      this->mqtt_client.connect("ArduinoClient");

      if (this->mqtt_client.connected()){
        Serial.println("Connected");
			}
      else{
				Serial.println("Not Connected");
				return false;
			}
  	}
    this->mqtt_client.publish(topic, data);
    this->mqtt_client.disconnect();
		return true;
}

char* UMqtt::add_mac_chipset(char *data){
  return data;
}

char* UMqtt::json_to_char(JsonObject& root){
  String payload;
  root.prettyPrintTo(payload);
  Serial.println("Payload:");
//  Serial.println(payload);

  char *jsonChar = new char[payload.length() + 1];
  strcpy(jsonChar, payload.c_str());
  Serial.println("JSONCHAR:");
//  Serial.println(jsonChar);

  return jsonChar;
}

