#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 2, 202 };
byte gateway[] = { 192, 168, 2, 1 };
byte subnet[] = { 255, 255, 255, 0 };

EthernetServer server(80);
String readString; 

void setup(){  
  pinMode(2, OUTPUT);
  
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

        if (readString.length() < 100) {
          readString += c; 
        } 
        
        if (c == '\n') {

          // Serial.println(readString);

          client.println("HTTP/1.1 200 OK");
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
          
          if(readString.indexOf("on") != -1)
          {
            // Serial.println(readString.indexOf("on"));            
            digitalWrite(2, LOW);
            // Serial.println("Led On");

          }
          if(readString.indexOf("off") != -1)
          {
            // Serial.println(readString.indexOf("off"));
            digitalWrite(2, HIGH);
            // Serial.println("Led Off");
          }
          readString="";

        }
      }
    }
  }
} 
