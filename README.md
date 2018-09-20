# UIoT Devices - Arduino

The objective of this library is to enable users to create *Clients* and *Services* that follow UIoT's Ontology of sending and managing message flows in Arduino devices.

All the protocols included as a means of communication in this library follow the same principles:
* Create a *Device*
* Create a *Service*
* Send *Data*

<!-- The documentation of the Ontology followed by this library can be found at @@link-ontologia -->


The supported protocols by supported are displayed in the following table  

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

# HTTP

  The HTTP library depends on the following libraries:

  <!-- * PubSubClient.h -->
  * EEPROM.h
  * Ethernet.h

  So, they must be installed in the users environment. The Ethernet library was used and tested to the @@nome-do-shield Ethernet Shield.

  ## Creating a Device

  A *Device* is an object of the UHttp class that represents the hardware whose means of communication protocol is the HTTP.

  To create a device using UHttp library you must create an instance of it, initialize it and, finally, set a server to send data to, as demonstrated below

  >```c++
  UHttp device;
  (...)
  device.init();
  device.set_server(SERVER_STRING);
  ```

  ## Creating a Service

  A *Service* in an object of the Service class that represents a task witch a *Device* has.

  To create a service using UHttp library you must create an instance of it and set a value from the [*UHttp.create_service*](#create_service) method as demonstrated below

  >```c++
  Service service1;
  (...)
  device.create_service(number, name, unit, numeric, parameter);
  ```
  ## Sending Data

  To send data to the specified server, you must use the [*UHttp.send_data*](#send_data) method as demonstrated below

  >```c++
    device.send_data(service1, ptr , tam, 0);
    ```


## Methods

### create_service

### send_data

```c++
    bool BaseProtocol::send_data(Service service, float *data, int array_size, int sensitive=0)
```



```c++
    bool BaseProtocol::send_data(Service service, char *char_data, int sensitive=0)
```


| Parameter | Type | Description | Obligatory |
|-|-|-|-|
| service | Service | Service object with the *services* characteristics | :heavy_check_mark:
| data | float* | Array of float values corresponding to the data collected from the service| :heavy_check_mark:
| array_size | int | number of values in the data array | :heavy_check_mark:
| sensitive | int | value that indicates if the data is sensitive or not, that is, if the data must bypass the gateways buffer (default value is 0 - not sensitive)| :x:
