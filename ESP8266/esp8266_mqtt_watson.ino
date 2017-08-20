/**
 * Helloworld style, connect an ESP8266 to the IBM IoT Foundation
 * 
 * Author: Ant Elder
 * License: Apache License v2
 */
#include <ESP8266WiFi.h>
#include <PubSubClient.h> // https://github.com/knolleary/pubsubclient/releases/tag/v2.3

//-------- Customise these values -----------
char* ssid = "Altibox492434";
char* password = "64cLQu8J";

#define ORG "bofe0l"
#define DEVICE_TYPE "ESP8266"
#define DEVICE_ID "ESP_01"
#define TOKEN "Qpu&dgdtznlpB2QDm5"
//-------- Customise the above values --------

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/evt/counter/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;
PubSubClient client(server, 1883, NULL, wifiClient);

void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 
  Serial.println("");

  Serial.print("WiFi connected, IP address: "); Serial.println(WiFi.localIP());
}

int counter = 0;

void loop() {

  if (!!!client.connected()) {
    Serial.print("Reconnecting client to ");
    Serial.println(server);
    while (!!!client.connect(clientId, authMethod, token)) {
      Serial.print(".");

      delay(500);
    }
    Serial.println();
  }
  String payload = "{\"d\":{\"counter\":";
  payload += counter;
  payload += "}}";

  //String payload = "{";
  //payload += "\"d\":\{\"counter\":";
  //payload += counter;
  //payload += "}}";
 
  Serial.print("Sending payload: ");
  Serial.println(payload);
 
  if (client.publish(topic, (char*) payload.c_str())) {
    Serial.println("Publish ok");
  } 
  else {
    Serial.println("Publish failed");
  }

  ++counter;
  delay(10000);
}

