#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 2, 202 };
byte gateway[] = { 192, 168, 2, 1 };
byte subnet[] = { 255, 255, 255, 0 };

EthernetServer server(80);
String readString; 

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);
DHT dht_out(4, DHTTYPE);

int R = 5;
int G = 6;
int B = 7;
int stateR;
int stateG;
int stateB;

int red;
int blue;
int green;

// RING
#include "HCWS2812.h"
HCWS2812 HCWS2812;

void setup(){  
  pinMode(3, OUTPUT);

  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  
  Ethernet.begin(mac, ip, gateway, gateway, subnet);
  server.begin();

  Serial.begin(9600); 

  // RING
  HCWS2812.SetBG(0, 0, 0);
  HCWS2812.ClearBuffer();
}

void loop(){

  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        if (readString.length() < 20) {
          readString += c; 
        } 
        
        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          
          if(readString.indexOf("weather") != -1) {
            
            float h = dht.readHumidity();
            float t = dht.readTemperature();
            float hic = dht.computeHeatIndex(t, h, false);
            
            client.println("Content-Type: application/json");
            client.println();
            client.print("{\n \"temperature\":");
            client.print(t);
            client.print(",\n \"humidity\":");
            client.print(h);
            client.print("\n}");

            delay(1);
  
            client.stop();
            
          }
          if(readString.indexOf("w_out") != -1) {
            
            float h = dht_out.readHumidity();
            float t = dht_out.readTemperature();
            float hic = dht_out.computeHeatIndex(t, h, false);
            
            client.println("Content-Type: application/json");
            client.println();
            client.print("{\n \"temperature\":");
            client.print(t);
            client.print(",\n \"humidity\":");
            client.print(h);
            client.print("\n}");

            delay(1);
  
            client.stop();
            
          }
          if(readString.indexOf("rgb_status") != -1) { 
            client.println("Content-Type: text/html");
            client.println();
            stateR = digitalRead(5);
            stateG = digitalRead(6);
            stateB = digitalRead(7);
            Serial.println(stateR);
            Serial.println(stateG);
            Serial.println(stateB);
            if(stateR == 1 || stateG == 1 || stateB == 1) {
              client.println("1");
            } else {
              client.println("0");
            }
            client.stop();
          }
          if(readString.indexOf("rgb_on") != -1) { 
            client.println("Content-Type: text/html");
            client.println();
            digitalWrite(5, HIGH);
            digitalWrite(6, HIGH);
            digitalWrite(7, HIGH);
            HCWS2812.SetBG(255, 255, 255);
            client.println("1");
            client.stop();
          }
          if(readString.indexOf("rgb_off") != -1) { 
            client.println("Content-Type: text/html");
            client.println();
            digitalWrite(5, LOW);
            digitalWrite(6, LOW);
            digitalWrite(7, LOW);
            client.println("0");
            client.stop();
          }
          if(readString.indexOf("rgb_brightness") != -1) { 
            client.println("Content-Type: text/html");
            client.println();
            client.println("0");
            client.stop();
          }
          if(readString.indexOf("rgb_set") != -1) { 
            client.println("Content-Type: text/html");
            client.println();
            client.println("ffffff");
            client.stop();
          }          
          if(readString.indexOf("rgb_light") != -1) { 
            client.println("Content-Type: text/html");
            client.println();
            Serial.println(readString.substring(16,19));
            client.println(readString.substring(16,19));
            client.stop();
          }
          if(readString.indexOf("rgb_hue") != -1) { 
            String hexstring = readString.substring(14,20);
            long number = (long) strtol( &hexstring[0], NULL, 16 );
            int red = number >> 16;
            int green = number >> 8 & 0xFF;
            int blue = number & 0xFF;
            setColor(red, green, blue);
            Serial.println(readString.substring(14,20));
            client.println("Content-Type: text/html");
            client.println();
            client.println(readString.substring(14,20));
            client.stop();
          }
          if(readString.indexOf("lamp_on") != -1) {          
            digitalWrite(3, HIGH);
            client.println("Content-Type: text/html");
            client.println();
            client.println("lamp on");
            client.stop();
          }
          if(readString.indexOf("lamp_off") != -1) {
            digitalWrite(3, LOW);
            client.println("Content-Type: text/html");
            client.println();
            client.println("lamp off");
            client.stop();
          }
          readString="";

        }
      }
    }
  }
} 

void setColor(int red, int green, int blue)
{
//  #ifdef COMMON_ANODE
//    red = 255 - red;
//    green = 255 - green;
//    blue = 255 - blue;
//  #endif
//  analogWrite(R, red);
//  analogWrite(G, green);
//  analogWrite(B, blue);  

  int index;
  
  /* Fill the output buffer with random colours */
  for(index = 0; index < 16; index++)
  {  
    RGBBuffer[RED][index] = red;
    RGBBuffer[GREEN][index] = green;
    RGBBuffer[BLUE][index] = blue;
  }
  
  //HCWS2812.SetBG(red, green, blue);
  HCWS2812.Refresh();
}
