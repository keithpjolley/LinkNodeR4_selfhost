#include <ESP8266WiFi.h>
//#include <WString.h>
#include <DNSServer.h>
//#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>

#define RELAY1 12
#define RELAY2 13
#define RELAY3 14
#define RELAY4 16
const int relays[] = {RELAY1, RELAY2, RELAY3, RELAY4};

// this is the deviceID that linksprite uses. not sure why not MAC address.
// for selfhosting it doesn't matter.
const char* deviceID   = "00800001eb";

const int   port = 80;
#define __KJ__LOCAL__
#ifdef  __KJ__LOCAL__
const char* server = "192.168.99.200"  // can use dns name ifn you wants
const char* path = "/linknode";
#else
const char* server = "www.linksprite.io";
const char* path = "/api/http";
#endif

void configWiFi();
void configGPIO();
void doUpdate(String json);
void doQuery(String json);

void setup() {
  Serial.begin(9600);
  //  Serial.println("setup start");
  configWiFi();
  configGPIO();
  //  Serial.println("setup end");
  return;
}

void loop() {
  //  Serial.println("loop");
  doQuery();
  return;
}

void configWiFi() {
  //  Serial.println("configWiFi start");
  WiFiManager wifiManager;
  wifiManager.setAPStaticIPConfig(IPAddress(10, 0, 1, 1), IPAddress(10, 0, 1, 1), IPAddress(255, 255, 255, 0));
  wifiManager.autoConnect("LinkNodeAP");
  //  Serial.println("WiFi connected");
  return;
}

void configGPIO() {
  for (int i = 0; i < sizeof(relays) / sizeof(int); i++) {
    pinMode(relay[i], OUTPUT);
    digitalWrite(relays[i],  LOW );
  }
  return;
}

// return the body or "" after POSTing "json"
String postJSON(String json) {
  //  Serial.println("postJSON - begin");
  String head, data, response = "";

  head  = "POST " + String(path) " HTTP/1.1"
  head += "Host: " + String(server) + "\n";
  head += "Content-Type: application/json\nContent-Length: " + json.length() + "\n\n";
  data  = head + json;
  response = "";

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(server, port)) {
    Serial.println("connection failed");
    return (response);
  }
  client.print(data);

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return (response);
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    response += client.readString();
  }

  client.stop();

  int index = response.indexOf("\r\n");
  if (index < 0) {
    return ("");
  }
  String stat = response.substring(0, index);
  index = stat.indexOf(" ");
  if (index < 0) {
    return ("");
  }
  stat = stat.substring(index + 1);
  index = stat.indexOf(" ");
  if (index < 0) {
    return ("");
  }
  stat = stat.substring(0, index);
  if (stat != "200") {
    return ("");
  }

  // body will be everything after separator
  String separator = "\r\n\r\n";
  String body = response.substring(response.indexOf(separator) + separator.length());
  return (body);
}


// query gets the state the server thinks the device should be in and sets it
int doQuery() {
  String jsonOUT = "{\"deviceid\":\"" + String(deviceID) + "\",\"action\":\"query\"}";
  String data = postJSON(jsonOUT);

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(data);

  if (!json.success()) {
    return (-1);
  }
  const char* jrays = json["relays"];
  Serial.print(jrays);
  Serial.print(" -> ");

  const int nrelays   = sizeof(relays) / sizeof(int);
  const int njrays = sizeof(jrays) / sizeof(char);
  if (npins != njrays) {
    Serial.println("oh noes. json 'relay' size does not match number of pins. panic, do something.");
    return (-1);
  }

  for (int i = 0; i < npins; i++) {
    digitalWrite(relays[i], ((jrays[i] == '0') ? LOW : HIGH));
    Serial.print((jrays[i] == '0') ? "_" : "-");
  }
  Serial.println("");
  return (0);
}

// udpate sends the server the state the device is in
int doUpdate() {
  //  String json = "{\"deviceid\":\"" + String(deviceID) + "\",\"action\":\"update\"}";
  //  String ret = postJSON(json);
  return (0);
}


