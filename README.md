# UIoT Devices

This librarys aim is to enable users to create *Clients* and *Services* that follow UIoT's Ontology of sending and managing message flows in Arduino devices.

All the protocols included as a means of communication in this library follow the same principles:

 1. Create a *Device*
 2. Create a *Service*
 3. Send *Data*

<!-- The documentation of the Ontology followed by this library can be found at @@link-ontologia -->


The supported protocols by supported devices are displayed in the following table  

<table>
<tr>
    <th>Device</th>
    <th>Protocol</th>
    <th>Example</th>
  </tr>
  <tr>
    <td rowspan = 1 ><a href="https://github.com/uiot/client_libraries/tree/master/UIoTDevices">Arduino</a></td>
    <td>HTTP</td>
      <td><a href="https://github.com/uiot/client_libraries/tree/master/UIoTDevices/examples/httpExampleArduino">httpExampleArduino</a></td>
  </tr>
  <tr>
    <td rowspan = 1><a href="https://github.com/uiot/client_libraries/tree/master/UIoTDevices_esp8266">Esp8266</a></td>
    <td>HTTP</td>
      <td><a href="https://github.com/uiot/client_libraries/tree/master/UIoTDevices_esp8266/examples/httpExampleEsp8266">httpExampleEsp8266</a></td>
  </tr>
  </table>


# Arduino

# HTTP

  The HTTP library depends on the following libraries:

  <!-- * PubSubClient.h -->
  * EEPROM.h
  * Ethernet.h

  So, they must be installed in the users environment. The Ethernet library was used and tested to the WizNet 5100 Ethernet Shield.

  ## Creating a Device

  A *Device* is an object of the UHttp class that represents the hardware whose means of communication protocol is the HTTP.

  To create a device using UHttp library you must create an instance of it, initialize it and, finally, set a server to send data to, as demonstrated below


  ```c++
  UHttp device;
  (...)
  device.init();
  device.set_server(SERVER_STRING);
  ```


## Creating a Service

  A *Service* in an object of the Service class that represents a task witch a *Device* has.

  To create a service using UHttp library you must create an instance of it and set a value from the [*UHttp.create_service*](#create_service) method as demonstrated below

  ```c++
  Service service1;
  (...)
  device.create_service(number, name, unit, numeric, parameter);
  ```

## Sending Data

  To send data to the specified server, you must use the [*UHttp.send_data*](#send_data) method as demonstrated below

  ```c++
    device.send_data(service1, ptr , tam, 0);
  ```


## Methods

### set_server


```c++
void UHttp::set_server(const char *server)
```


| Parameter | Type | Description | Obligatory |
|-|-|-|-|
| server | char* | array of characters that contains the servers domain or IP[1] | :heavy_check_mark:

[1]The servers port is set to 8000 byt default, to change it you must define your a variable called *HTTP_PORT* in your code.

### create_service

```c++
int BaseProtocol::create_service(int number, const char *name, String unit, bool numeric, String parameter)
```

| Parameter | Type | Description | Obligatory |
|-|-|-|-|
| number | int | Number to be attributed to the Service object that is beeing created | :heavy_check_mark:
| name | char* | Array of characters that mounts the name of the Service object that is beein created| :heavy_check_mark:
| unit | String | String that contais the unit of the value that is produced by the Service object that is beeing createed | :heavy_check_mark:
| numeric | bool | Value that indicates if the data produced by the service is of a numeric type or not | :heavy_check_mark:
| parameter | String | Value that indicates the parameters of the Service object that is beeing created | :heavy_check_mark:


### send_data

```c++
    bool BaseProtocol::send_data(Service service, float *data, int array_size, int sensitive=0)
```

| Parameter | Type | Description | Obligatory |
|-|-|-|-|
| service | Service | Service object with the *services* characteristics | :heavy_check_mark:
| data | float* | Array of float values corresponding to the data produced from the service| :heavy_check_mark:
| array_size | int | number of values in the data array | :heavy_check_mark:
| sensitive | int | value that indicates if the data is sensitive or not, that is, if the data must bypass the gateways buffer (default value is 0 - not sensitive)| :x:


```c++
    bool BaseProtocol::send_data(Service service, char *char_data, int sensitive=0)
```

| Parameter | Type | Description | Obligatory |
|-|-|-|-|
| service | Service | Service object with the *services* characteristics | :heavy_check_mark:
| char_data | float* | Array of characters with the value corresponding to the data produced from the service| :heavy_check_mark:
| sensitive | int | value that indicates if the data is sensitive or not, that is, if the data must bypass the gateways buffer (default value is 0 - not sensitive)| :x:

<!-- TODO# Serial -->
