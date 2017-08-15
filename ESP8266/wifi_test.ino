// Import ESP8266 wifi library
#include "ESP8266WiFi.h"

// WiFi parameters
char* ssid = "Windows 10 Update";
char* pwd = "DefNotAVirus";

void setup(void)
{ 
// Start Serial Communication
Serial.begin(115200);

// Connect to WiFi
WiFi.begin(ssid, pwd);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

// Print the IP address
Serial.println(WiFi.localIP());

}

void loop() {

}
