#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ThingerWifi.h>
#include <SimpleTimer.h>
#include <EEPROM.h> 

char* thingerUser = "MYUSERNAME";
char* myDeviceKey = "MYDEVICEKEY";
char* myDeviceName = "esp8266_1";
ThingerWifi thing(thingerUser, myDeviceName, myDeviceKey);

int MSW = 0;                          // Magnetic switch
int SW = 2;                           // Garage door opener switch

byte switchToggleDoorOpen = 0;
byte doorState= 0;                    // 1 = open, 2 = just closed, 3 = closed, 4 = just opened)"
byte prevDoorState = 0;               // 0 = "Open", 1 = "Closed"
byte currDoorState = 0;               // 0 = "Open", 1 = "Closed"
String doorStatus = "";               // "Door has been open for X min", "Door is closed"

unsigned int doorStartTime_ms = 0;
unsigned int doorTimeInterval_ms = 0;
unsigned int autoCloseTimer = 0;
byte autoCloseInterval = 0;

byte doorAlertInterval = 0;
unsigned long doorAlertTimer = 0;

SimpleTimer timer;
int doorStateTimerId;
int functionCallSpeed_ms = 100;

void setup(){

  EEPROM.begin(512);
  doorAlertInterval = EEPROM.read(0);
  autoCloseInterval = EEPROM.read(1);    
  
  pinMode(SW, OUTPUT);
  pinMode(MSW, INPUT_PULLUP);
  digitalWrite(SW, LOW);
  
  currDoorState = readDoorState();
  if (currDoorState == 1)
  {
    doorStartTime_ms = millis();
    doorStatus = "Open";
  }
  else
  {
    doorStatus = "Closed";
    doorTimeInterval_ms = 0;
  }
  delay(50);

  doorStateTimerId = timer.setInterval(functionCallSpeed_ms, checkDoorState);
  
  thing.add_wifi("Altibox492434", "64cLQu8J");
  
  thing["garageDoorSwitch"] << [](pson& sw)
  {
    if(sw.is_empty())
      sw = false;
    else
      toggle_switch();
  };
  
  thing["doorStatus"] >> [](pson& out)
  {
    out = doorStatus;
  };

  thing["autoCloseInterval"] << inputValue(autoCloseInterval,
  {
    autoCloseTimer = (doorTimeInterval_ms / 60000) + autoCloseInterval;
    EEPROM.write(1, autoCloseInterval);
    EEPROM.commit();   
  });
  
  thing["doorAlertInterval"] << inputValue(doorAlertInterval,{
    doorAlertTimer = (doorTimeInterval_ms / 60000) + doorAlertInterval;    
    EEPROM.write(0, doorAlertInterval);
    EEPROM.commit();  
  });

  thing["doorStatusTimeInterval"] >> [](pson& out)
  {
    String doorStatusTimeInterval;
    if (doorStatus == "Open")
    {      
       int seconds = doorTimeInterval_ms%60000;
       seconds = seconds/1000;
       doorStatusTimeInterval = String("Door has been OPEN for ") + (doorTimeInterval_ms / 60000) + String("m ") +  seconds + String("s");
    } 
    else if (doorStatus == "Closed")
    {
       doorStatusTimeInterval = String("Door is closed");
    }
    else
    {
       doorStatusTimeInterval = String("Door in unknown state");
    }
    out = doorStatusTimeInterval.c_str();
  };
}
void loop()
{
  timer.run();
  thing.handle();
}

void door_alert() 
{
    pson data;
    data["The garage door has been OPEN for"] = doorTimeInterval_ms / 60000;
    thing.call_endpoint("doorAlert", data);
}

void toggle_switch()
{
  digitalWrite(SW, HIGH);
  delay(500);
  digitalWrite(SW, LOW);  
}

byte readDoorState()
{
  if (digitalRead(MSW))
    return 0;
  else
    return 1;    
}

byte checkDoorState(byte x, byte y){
  byte state;  
  if (x != 0 && y != 0){
    state = 1;
  }
   if (x == 0 && y != 0){
    state = 2;
  }
   if (x == 0 && y == 0){
    state = 3;
  }
  if (x != 0 && y == 0){
    state = 4;
  }  
  return state;
}

void checkDoorState()
{
  prevDoorState = currDoorState;     
  currDoorState = readDoorState();
  doorState = checkDoorState(currDoorState, prevDoorState);
  switch (doorState) {
    case 1:
          doorTimeInterval_ms = (millis() - doorStartTime_ms);              
          if (autoCloseInterval != 0){                           
              if (doorTimeInterval_ms >= autoCloseTimer * 60000){
                  toggle_switch();
                  autoCloseTimer = (doorTimeInterval_ms / 60000) + autoCloseInterval;                                     
              }                                  
          }
          if (doorAlertInterval != 0){                           
              if (doorTimeInterval_ms >= doorAlertTimer * 60000){
                  door_alert();
                  doorAlertTimer = (doorTimeInterval_ms / 60000) + doorAlertInterval;                                     
              }                                  
          }          
          break;
    case 2:
          doorStatus = "Closed"; 
          doorTimeInterval_ms = 0;              
          autoCloseTimer = autoCloseInterval;
          doorAlertTimer = doorAlertInterval; 
          thing.write_bucket("garageBucket", "doorStatus");
          break;
    case 3:
          break;
    case 4:
          doorStartTime_ms = millis(); 
          doorStatus = "Open";                           
          thing.write_bucket("garageBucket", "doorStatus");
          break;    
  }  
}
