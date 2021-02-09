/*
   ESP8266 NodeMCU AJAX Demo
   Updates and Gets data from webpage without page refresh
   https://circuits4you.com
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include "index.h"
#include "manifest.h"


#define LED 2  //On board LED


byte tanks[2] = {0, 0}; // where the read value is stored for all tanks.


//SSID and Password of your WiFi router
const char* ssid = "tanks";
const char* password = "10203040";

// Create AsyncWebServer object on port 80
ESP8266WebServer server(80);


void setup(void) {
  Serial.begin(300);
  WiFi.softAP(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  //Onboard LED port Direction output
  pinMode(LED, OUTPUT);
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
#ifdef DEBUG
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
#endif

  server.on ( "/", []() {
    server.send ( 200, "text/html", SITE_index );
  } );
  server.on ( "/manifest.webmanifest", []() {
    server.send ( 200, "text/json", manifest );
  } );
  server.on("/read", handleread);
  server.begin();                  //Start server
#ifdef DEBUG
  Serial.println("HTTP server started");
#endif
}
void handleread() {

  String value = bits_count(0b10000000 & tanks[0]) + bits_count(0b01111111 & tanks[0]) + bits_count(0b10000000 & tanks[1]) + bits_count(0b01111111 & tanks[1]);
  server.send(200, "text/plane", value ); //Send ADC value only to client ajax request
}
String bits_count(byte value)
{
  int count = 0;
  for (int i = 0; i < 8; i++)
  {
    if (bitRead(value, i))
      count++;
  }
  return String(count);
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void) {
  server.handleClient();
  if (Serial.available() > 0) {
    Serial.readBytes(tanks, 2);

#ifdef DEBUG
    Serial.println("recieved");
    Serial.print(tanks[0]);
    Serial.print(tanks[1]);
#endif
  }


}
