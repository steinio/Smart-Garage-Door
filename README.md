# Smart Garage Door
This will be a repository for a smart garage door project.

This project was spawned from myself always forgetting to close the garage door when leaving the house and when parking the car. 

The current garage door is opened and closed by an electric motor and is controlled by wireless switches (one in the car and one in the house), aswell as a wired switch inside the garage. The door is planned to be controlled  via the same input as the wired switch, which runs on 18V.

## Project Objective

The goal is the create a solution that automatically closes the garage door after I have left or come home. So some of the logic then revolves around cases such as 

- I have opened the door when the garage is empty.
- The garage door is open but there is movement inside the garage.
- The garage door is open and there is movement right outside of the garage.

### Planned Features

- To automatically open when the car is coming up the driveway (only my car).
- Remote control and monitoring on the web on both smart phone (app) and computer.
- License plate detection.

The project is ment to be an IoT, embedded and computer vision learning project for myself, while making something I can use in my daily life.

### Planned Hardware

- Raspberry Pi 3 B+
- Raspberry Pi Noir V2 Camera
- Low cost web camera
- Arduino nano/uno
- ESP8266
- Solid state relay
- Motion sensor
- Proximity sensor
- Humidity and temperature sensor (not needed, just because)

### Planned Software, Platforms and Languages

- IBM Bluemix
- Arduino IDE
- C (ESP8266 and Arduino)
- C++ (Raspberry Pi server application)
- Java (Android app)
- MQTT

The hardware for the project is still arriving from the hardworking republic of China, so stay tuned.

## Day 1 - Initial Testing

The components have all arrived, so now there are no more excuses.

First thing I want to do is to see if I can compile a simple program on the ESP8266, and get it connected to my WiFi, since this is the most important component in this project.

I decided to use the Arduino IDE to program the ESP8266, as this is the framework I am most experienced with.
To do this you first have to add the ESP9266 board by using the board manager in the Arduino IDE, by following the 3 steps below.

- Open the Preferences window.
- Enter the URL: [http://arduino.esp8266.com/package_esp8266com_index.json](http://arduino.esp8266.com/package_esp8266com_index.json) into Additional Board Manager URLs field.
- Open Boards Manager from Tools > Board menu and install the ESP8266 platform.

After that you select the Generic ESP8266, before uploading the code.
But to upload code, it needs to be connected to your computer somehow.

The ESP8266 can be hooked up by using an FTDI, which is serial to usb, connected as shown below.
![](https://github.com/steinio/Smart-Garage-Door/blob/master/Images/esp8266toFTDI.png)

Just to be sure that the device actually works before uploading my own code, I will test the AT interface over serial to see if I can get a response.
This is done by opening the serial monitor and write "AT\r\n" and click send, at 115200 baud rate.
You should then receive an "OK" message in response if everything is working, which it did.

The WiFi test code is quite simple, made possible by the ESP8266 wifi library.

```
// Import required libraries
#include "ESP8266WiFi.h"

// WiFi parameters
const char* ssid = "Windows 10 Update";
const char* password = "DefNotAVirus";

void setup(void)
{ 
// Start Serial
Serial.begin(115200);

// Connect to WiFi
WiFi.begin(ssid, password);
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
```
When running, this should print out "WifI connected" followed by the IP address it was given.

After connecting my RX to my TX instead of the RX from my FTDI to the ESP8266, I could finally upload some code to my device and see that everything is working as it should.
