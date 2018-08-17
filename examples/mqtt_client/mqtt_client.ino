

#include <Ethernet.h>
//#include <PubSubClient.h>
#include <UMqtt.h>


// Ethernet parameters:
byte mac[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xFA, 0x06 };
EthernetClient ethernet_client;

// MQTT parameters:
IPAddress server(192, 168, 0, 109);


void setup() {

  // Communication between user and Arduino via Serial:
  Serial.begin(9600);
  while(!Serial);


  // Start the Ethernet connection:
//  Serial.println("Getting IP Address");
//  Ethernet.begin(mac);
//  delay (1000);

  // Print the local IP address, if connected:
  //print_ip_address();


  //Class-made Client
  UMqtt class_client(ethernet_client, server);
  Service service1 = class_client.create_service(1, "getTemp", "°C", true, "Temperatura");
  class_client.send_data(service1, (char*)"56", 0);

//Raw Client Manufacture
//  PubSubClient mqtt_client;
//  mqtt_client.setClient(ethernet_client);
//  mqtt_client.setServer(server, 1883);
//
//  connect_to_broker(mqtt_client, "RawPubSub");
//
//  Serial.println("Publishing Manufactured PubSubClient from Client RawPubSub");
//  Serial.println(MQTT_MAX_PACKET_SIZE);
//  mqtt_client.publish("D", "{\"number\":3,\"chipset\":\"AAAAAAAAAAAAAAAAAAAAAAA\",\"mac\":\"AAAAAAAAAAAAAAAAA\",\"name\":\"getTemp\",\"parameter\":\"123456789012345\"");
//  mqtt_client.disconnect();

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("loop");
  delay(10000);

}


void print_ip_address (void) {
  Serial.print ("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print (Ethernet.localIP ()[thisByte], DEC);
    Serial.print (".");
  }

  Serial.println ();
}

//loop that assures connection to broker
//TODO = Better solution
void connect_to_broker(PubSubClient c, const char* client_name){
  while(!c.connected()){
  Serial.println("Connecting...");
  c.connect(client_name);

  if (c.connected()){
    Serial.println("Connected");
  }
  else{
    Serial.println("Not Connected");
  }
  delay(1500);
  }
}
