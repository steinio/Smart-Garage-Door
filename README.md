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
