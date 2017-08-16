![](Images/garagedoor.jpg "Smart Garage Door")

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

First thing I did was to see if I could compile a simple program on the ESP8266, and get it connected to my WiFi, since this is the most important component in this project.

I decided to use the Arduino IDE to program the ESP8266, as this is the framework I am most experienced with.
To do this I first had to add the ESP9266 board by using the board manager in the Arduino IDE, by following the 3 steps below.

- Open the Preferences window.
- Enter the URL: [http://arduino.esp8266.com/package_esp8266com_index.json](http://arduino.esp8266.com/package_esp8266com_index.json) into Additional Board Manager URLs field.
- Open Boards Manager from Tools > Board menu and install the ESP8266 platform.

After that I selected the Generic ESP8266, before uploading the code.
But to upload code, it needs to be connected to my computer somehow.

I connected the ESP8266 by using an FTDI, which is serial to usb, connected as shown below.

![](Images/esp8266toFTDI.png "ESP8266 to FTDI wire scheme")

Just to be sure that the device actually works before uploading my own code, I tested the AT interface over serial to see if I could get a response.
This was done by opening the serial monitor and sending the string "AT\r\n", at 115200 baud rate.
I then received an "OK" message in response, meaning that everything was working.
We can now start writing and uploading our own code to the device.

When uploading new code the device has to be in bootloader mode, which is done by connecting the GPIO_0 pin to ground and powering the device off and on again.
To run the code after uploading, simply disconnect GPIO_0 from ground and power it off and on once more.

The WiFi test code I uploaded is quite simple, made possible by the ESP8266 wifi library.

```c_cpp
// Import ESP8266 wifi library
#include "ESP8266WiFi.h"

// WiFi parameters
char* ssid = "Windows 10 Update";
char* pwd = "DefNotAVirus";

void setup(void)
{ 
// Start Serial Connection
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
```
When running, this printed out 
```
Wifi connected
192.168.1.245
```
