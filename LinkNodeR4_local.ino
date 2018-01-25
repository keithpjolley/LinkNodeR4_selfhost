#include <ESP8266WiFi.h>
#include <WString.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

String data;
bool config_flag = true;
//WiFiClient client;

#define __KJ__LOCAL__
#ifdef  __KJ__LOCAL__
const char* server = "localhost";
const char* path = "/linknode";
#else
const char* server = "www.linksprite.io";
const char* path = "/api/http";
#endif

const int   port = 80;
const char* deviceID   = "00800001eb";

void config_wifi();
void doUpdate(String a);
void doQuery(String a);
void config_gpio();

void setup() {
  Serial.begin(230400);
  Serial.println("##############################################################################");
  delay(1000);
  Serial.print("begin...");
  delay(1000);
  Serial.println(" now.");
  config_wifi();
  config_gpio();
}

void loop() {
  delay(5000);
  doQuery();
}

void config_wifi() {
  WiFiManager wifiManager;
  wifiManager.setAPStaticIPConfig(IPAddress(10, 0, 1, 1), IPAddress(10, 0, 1, 1), IPAddress(255, 255, 255, 0));
  wifiManager.autoConnect("LinkNodeAP");
  Serial.println("WiFi connected");
}

void config_gpio() {
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(16, OUTPUT);
}

String sendJson(String json) {
  String head = "POST " + String(path) + " HTTP/1.1\nHost: " + String(server) + "\nContent-Type: application/json\nContent-Length: " + json.length();
  String data = head + "\n\n" + json + "\n";

  String ret = "";

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(server, port)) {
    Serial.println("connection failed");
    return "";
  }
  Serial.println("Requesting data: ### BEGIN ############################################################");
  Serial.println(data);
  Serial.println("Requesting data: ### END   ############################################################");

  // This will send the request to the server
  client.print(data);
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return ret;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  client.stop();

  return ret;
}

// query gets the state the server thinks the device should be in and sets it
int doQuery() {
  String json = "{\"deviceid\":\"" + String(deviceID) + "\",\"action\":\"query\"}";
  String ret = sendJson(json);
  Serial.println("doQuery: RECEIVED: ");
  Serial.println(ret);
  Serial.println("doQuery: RECEIVED: ");
  return 0;
}

// udpate sends the server the state the device is in
int doUpdate() {
  String json = "{\"deviceid\":\"" + String(deviceID) + "\",\"action\":\"query\"}";
  String ret = sendJson(json);
  Serial.print("registerDevice: RECEIVED: ");
  Serial.println(ret);
  return 0;
}


