#include <UHttp.h>


UHttp cliente;
Service service1;
int tam = 10;

void setup(){
  Serial.begin(9600);
  while (!Serial);
  delay(1000);
  cliente.init();
  cliente.set_server("172.16.9.69");
  service1 = cliente.create_service(1, "getTemp", "*C", 1, "Temperatura");
}

void loop(){
  float* ptr = gerador_array(tam);
  cliente.send_data(service1, ptr , tam, 0);
  delay(5000);
  Serial.println("loop");
  free(ptr);

}

float* gerador_array(int tamanho){
  float *values;
  values = (float*)malloc(tamanho*sizeof(float));
  for(int i = 0; i < tamanho; i++){
    values[i] = random(2,100) + random(0,999)/1000;
  }
  Serial.print("Random Values:");
  for(int i = 0; i < tamanho; i++){
    Serial.print(values[i]);
    Serial.print(" - ");
  }
  return values;
}
