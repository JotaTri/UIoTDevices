#include "UHttp.h"

UHttp::UHttp(){
  // this->device_identificator();
  // Ethernet.begin(this->mac_byte);

  // Serial.print ("My IP address: ");
  // for (byte thisByte = 0; thisByte < 4; thisByte++) {
  //   Serial.print (Ethernet.localIP ()[thisByte], DEC);
  //   Serial.print (".");
  // }
  // Serial.println("");
}


UHttp::UHttp(const char *server){
  this->device_identificator();

  this->server = server;
  Ethernet.begin(this->mac_byte);

  Serial.print ("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    Serial.print (Ethernet.localIP ()[thisByte], DEC);
    Serial.print (".");
  }
  Serial.println("");
}

void UHttp::init(){
  this->device_identificator();

  Ethernet.begin(this->mac_byte);

  Serial.print ("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    Serial.print (Ethernet.localIP ()[thisByte], DEC);
    Serial.print (".");
  }
  Serial.println("");
}


void UHttp::set_server(const char *server){
  Serial.println("set_server");
  this->server = server;
}

bool UHttp::register_device(){
  char *data;
  data = this->make_client_data();

  return this->POST("/client", data);
}

bool UHttp::register_service(Service s){
  char *data;
  data = this->make_service_data(s);

  return this->POST("/service", data);
}

bool UHttp::register_data(Service s, char* value, int sensitive){
  char *data;
  data = this->make_raw_data(s, value, sensitive);

  return this->POST("/data", data);
}

bool UHttp::POST(const char* endpoint, char* post_data){
  Serial.print("Attempting to post:");
  Serial.println(post_data);
  Serial.print("To ");
  Serial.print(this->server);
  Serial.print(":");
  Serial.println(HTTP_PORT);
  if(this->eth_client.connect(this->server,HTTP_PORT)){
    Serial.println("H0");
    this->eth_client.print("POST ");
    this->eth_client.print(endpoint);
    this->eth_client.println(" HTTP/1.1");
    Serial.print("POST ");
    Serial.print(endpoint);
    Serial.println(" HTTP/1.1");
    // this->eth_client.println("User-Agent: Arduino");

    this->eth_client.println("Host: 192.168.0.109");
    Serial.println("Host: 192.168.0.109");
    this->eth_client.println("Connection: close");
    Serial.println("Connection: close");
    this->eth_client.println("Content-Type: application/json");
    Serial.println("Content-Type: application/json");
    this->eth_client.print("Content-Length: ");
    this->eth_client.println(strlen(post_data));
    Serial.print("Content-Length: ");
    Serial.println(strlen(post_data));
    this->eth_client.println();
    this->eth_client.println(post_data);
    Serial.println();
    Serial.println(post_data);
    delay(10);
    this->eth_client.flush();
    this->eth_client.stop();
    Serial.println(this->eth_client.read());
    // 
    // while(this->eth_client.connected()){
    //   while(this->eth_client.available()){
    //     Serial.write(this->eth_client.read());
    //   }
    // }

    Serial.println("Posted sepa");
    delay(100);
    return true;
  }
  else{
    Serial.print("Connection to server '");
    Serial.print(this->server);
    Serial.println("' failed");
    return false;
  }
}
