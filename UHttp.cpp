#include "UHttp.h"

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

void UHttp::set_server(const char *server){
  this->server = server;
}

bool UHttp::POST(const char* endpoint, char* post_data){
  Serial.print("Attempting to post:");
  Serial.println(post_data);
  Serial.println("H-1");
  if(this->eth_client.connect(this->server,HTTP_PORT)){
    Serial.println("H0");
    this->eth_client.print("POST ");
    this->eth_client.print(endpoint);
    this->eth_client.println("HTTP/1.1");
    Serial.println("H1");
    // this->eth_client.println("User-Agent: Arduino");
    Serial.println("H2");
    this->eth_client.println("Host: 192.168.0.102");
    Serial.println("H3");
    this->eth_client.println("Connection: close");
    Serial.println("H4");
    this->eth_client.println("Content-Type: application/json");
    Serial.println("H5");
    this->eth_client.print("Content-Length: ");
    this->eth_client.println(strlen(post_data));
    Serial.println("H6");
    this->eth_client.println();
    this->eth_client.println(post_data);
    Serial.println("H7");
    this->eth_client.flush();
    this->eth_client.stop();
    Serial.println("H8");

    while(this->eth_client.connected()){
      while(this->eth_client.available()){
        Serial.write(this->eth_client.read());
      }
    }

    Serial.println("Posted sepa");

    return true;
  }
  else{
    Serial.print("Connection to server '");
    Serial.print(this->server);
    Serial.println("' failed");
    return false;
  }
}
