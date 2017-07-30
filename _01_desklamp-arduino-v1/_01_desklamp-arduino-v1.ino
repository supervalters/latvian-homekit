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
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

void setup(){  
  pinMode(3, OUTPUT);
  
  Ethernet.begin(mac, ip, gateway, gateway, subnet);
  server.begin();

  Serial.begin(9600); 
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
            
          } else {
            client.println("Content-Type: text/html");
            client.println();
  
            client.println("<HTML>");
            client.println("<HEAD>");
            client.println("<TITLE>Desk Lamp web switch</TITLE>");
            client.println("</HEAD>");
            client.println("<BODY>");
  
            client.println("<H1>Desk Lamp web switch</H1>");
            
            client.println("<a href=\"/?on\">ON</a>"); 
            client.println("<a href=\"/?off\">OFF</a>"); 
  
            client.println("</BODY>");
            client.println("</HTML>");
  
            delay(1);
  
            client.stop();

            if(readString.indexOf("on") != -1) {          
              digitalWrite(3, LOW);
            }
            if(readString.indexOf("off") != -1) {
              digitalWrite(3, HIGH);
            }
          }
          readString="";

        }
      }
    }
  }
} 
