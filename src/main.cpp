#include <Arduino.h>
#include "WiFi.h"
#include "AsyncUDP.h"
#include "Joystick.h"
#include "Potentiometer.h"


const char * ssid = "AndroidAPC910";
const char * password = "fnsa6355";

AsyncUDP udp;

//Joystick
int pinX = 36;   
int pinY = 39;
int prevX;
int prevY;
int tolerance = 200;

//Potentiometer
int potentiometer = 34;
int sensorvalue;
int preValue;
int tolllerence = 130;

void setup(){

    //Joystick
    Serial.begin(9600);
    pinMode(pinX, INPUT);
    pinMode(pinY, INPUT);
    pinMode(13, INPUT_PULLUP);
    prevX = analogRead(pinX);
    prevY = analogRead(pinY);

    //Potentiometer
    pinMode(potentiometer,INPUT);
    
    //Connection to pxlserver
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
       
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        while(1) {
            delay(1000);
        }
    }
    if(udp.listen(7007)) {
        Serial.print("UDP Listening on IP: ");
        Serial.println(WiFi.localIP());
        udp.onPacket([](AsyncUDPPacket packet) {
            Serial.print("UDP Packet Type: ");
            Serial.print(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
            Serial.print(", From: ");
            Serial.print(packet.remoteIP());
            Serial.print(":");
            Serial.print(packet.remotePort());
            Serial.print(", To: ");
            Serial.print(packet.localIP());
            Serial.print(":");
            Serial.print(packet.localPort());
            Serial.print(", Length: ");
            Serial.print(packet.length());
            Serial.print(", Data: ");
            Serial.write(packet.data(), packet.length());
            Serial.println();
            //reply to the client
            packet.printf("Got %u bytes of data", packet.length());
            Serial.print("state: ");
        /*  Serial.write(packet.data(), packet.length());
            String s((char*)packet.data());
            s = s.substring(0, packet.length()); 
            s.trim();
            // send string to method
            Serial.println(s);
            udp.printf("Received your message!");
        */
        });
    }

        //Send unicast
        //udp.print("Hello Server!");
        //udp.
        
    }


void loop(){

    //Potentiometer
    sensorvalue = analogRead(potentiometer);
    if (sensorvalue > tolllerence + preValue || sensorvalue < preValue - tolllerence) {
    Serial.println(sensorvalue);
    preValue = sensorvalue;
    } else {
    sensorvalue = preValue;
    }
   
    //Joystick
    if(abs(analogRead(pinX) - prevX) > tolerance || 
    abs(analogRead(pinY) - prevY) > tolerance) {
    //Serial.print(map(analogRead(pinX), 0, 4095, -100, 100));
    Serial.print(prevX);
    Serial.print(" : ");
    Serial.println(prevY);
    //Serial.println(map(analogRead(pinY), 0, 4095, 100, -100));
    prevX = analogRead(pinX);
    prevY = analogRead(pinY);
    }

    //pxlserver pixel color
    if (sensorvalue < 400) { 
        udp.writeTo((const uint8_t*)"color 80 20 50", 14, IPAddress(192,168,43,255), 7000);
    }    
    if (sensorvalue > 400 && sensorvalue < 800) { 
        udp.writeTo((const uint8_t*)"color 200 200 200", 17, IPAddress(192,168,43,255), 7000);
    }    
    if (sensorvalue > 800 && sensorvalue < 1200) { 
        udp.writeTo((const uint8_t*)"color 50 50 50", 14, IPAddress(192,168,43,255), 7000);
    }   
    if (sensorvalue > 1600 && sensorvalue < 2000) { 
        udp.writeTo((const uint8_t*)"color 100 50 200", 16, IPAddress(192,168,43,255), 7000);
    }   
    if (sensorvalue > 2000 && sensorvalue < 2400) { 
        udp.writeTo((const uint8_t*)"color 50 200 200", 16, IPAddress(192,168,43,255), 7000);
    }   
    if (sensorvalue > 2400 && sensorvalue < 2800) { 
        udp.writeTo((const uint8_t*)"color 50 200 100", 16, IPAddress(192,168,43,255), 7000);
    }   
    if (sensorvalue > 3200 && sensorvalue < 3600) { 
        udp.writeTo((const uint8_t*)"color 20 50 50", 14, IPAddress(192,168,43,255), 7000);
    }
    if (sensorvalue > 3600 && sensorvalue < 4000) { 
        udp.writeTo((const uint8_t*)"color 90 100 80", 15, IPAddress(192,168,43,255), 7000);
    }   
  
    
    //Write to pxlserver from joystick
    if (digitalRead(13) == LOW){
        udp.writeTo((const uint8_t*)"init 10 10", 10, IPAddress(192,168,43,255), 7000);
    }
    if (prevY > 2000){
        udp.writeTo((const uint8_t*)"moveup", 6, IPAddress(192,168,43,255), 7000);
    }
    
    if (prevY < 1000){
        udp.writeTo((const uint8_t*)"movedown", 8, IPAddress(192,168,43,255), 7000);
    }
    if (prevX < 1000){
        udp.writeTo((const uint8_t*)"moveright", 9, IPAddress(192,168,43,255), 7000);
    }
    if (prevX > 2000){
        udp.writeTo((const uint8_t*)"moveleft", 8, IPAddress(192,168,43,255), 7000);
    }

    

    //delay(5000);
    //Send broadcast on port 7000
    udp.broadcastTo("Anyone here?", 7000);
    //Serial.println("waiting for udp message...");
    // IPAssress i denne linje er det wifi netwærk jeg er koblet op på
    // find ved Terminal: ifconfig, under "inet"
    
    

    //udp.writeTo((const unit8_t*))
    //udp.writeTo()

}