#include "UMqtt.h"

UMqtt::UMqtt(Client& client, IPAddress server) {
  this->device_identificator();

 Serial.println("Getting IP Address");
 Ethernet.begin(this->mac_byte);
 //byte m[] = { 0x9A, 'I', 'O', 'T', 0xFB, 0x06 };
 //Ethernet.begin(m);
 Serial.print ("My IP address: ");
 for (byte thisByte = 0; thisByte < 4; thisByte++) {
   // print the value of each byte of the IP address:
   Serial.print (Ethernet.localIP ()[thisByte], DEC);
   Serial.print (".");
 }

 Serial.println ();

  delay (1000);

	this->mqtt_client.setClient(client);
  this->mqtt_client.setServer(server, this->mqtt_port);
}

bool UMqtt::register_device(){
  char *data;
  data = this->make_client_data();
  // Serial.println(data);
  return this->publish("C", data);
}

bool UMqtt::register_service(Service service){
  char *data;
  data = this->make_service_data(service);

  return this->publish("S", data);
}

bool UMqtt::register_data(Service service, char  *data, int sensitive){
  char *full_data;
  full_data = this->make_raw_data(service, data, sensitive);

  return this->publish("D", full_data);
}

bool UMqtt::publish(const char *topic, char *data) {
    this->mqtt_client.connect((char*)this->mac.c_str());
    if (!this->mqtt_client.connected()){
      Serial.println("Could not connect to broker!");
      return false;
    }
    Serial.println(MQTT_MAX_PACKET_SIZE);
    bool isSent = this->mqtt_client.publish(topic, data);
    this->mqtt_client.disconnect();
    Serial.println(isSent);
    return isSent;
}

char* UMqtt::add_mac_chipset(char *data){
  return data;
}

char* UMqtt::json_to_char(JsonObject& root){
  String payload;
  // root.prettyPrintTo(payload);
  Serial.println("Payload:");
//  Serial.println(payload);

  char *jsonChar = new char[payload.length() + 1];
  strcpy(jsonChar, payload.c_str());
  Serial.println("JSONCHAR:");
//  Serial.println(jsonChar);

  return jsonChar;
}
