#include <UHttp.h>

void setup(){
  
}

void loop(){
  delay(5000);
  Serial.println("loop");
}
//#include <ArduinoJson.h>
//#include <ESP8266HTTPClient.h>
//#include <ESP8266WiFi.h>
// 
//void setup() {
// 
//  Serial.begin(115200);                                  //Serial connection
//  WiFi.begin("Trojan 2.0", "Ologineasenh4!");   //WiFi connection
// 
//  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
// 
//    delay(500);
//    Serial.println("Waiting for connection");
// 
//  }
// 
//}
// 
//void loop() {
// 
// if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
//   Serial.println("CONECTOU");
//   HTTPClient http;    //Declare object of class HTTPClient
//   http.begin("http://192.168.1.103:5000/formula");      //Specify request destination
//   http.addHeader("Content-Type", "application/json");  //Specify content-type header
//// 
//
//    StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
//    JsonObject& JSONencoder = JSONbuffer.createObject(); 
// 
//    JSONencoder["formula"] = "TESTE";
//
//    char JSONmessageBuffer[300];
//    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
//    Serial.println(JSONmessageBuffer); 
//
//   int httpCode = http.POST(JSONmessageBuffer);   //Send the request
//   String payload = http.getString();                  //Get the response payload
// 
//   Serial.println(httpCode);   //Print HTTP return code
//   Serial.println(payload);    //Print request response payload
// 
//   http.end();  //Close connection
// 
// }else{
// 
//    Serial.println("Error in WiFi connection");   
// 
// }
// 
//  delay(30000);  //Send a request every 30 seconds
// 
//}
