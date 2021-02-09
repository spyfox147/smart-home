/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-websocket-server-arduino/
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "index.h"
#include "manifest.h"
#include <DNSServer.h>

// Replace with your network credentials
const char* ssid = "tanks";

const char* password = "10203040";

byte tanks[2] = {0, 0}; // where the read value is stored for all tanks.

DNSServer dnsServer;
const byte DNS_PORT = 53;


// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");


void notifyClients() {
  String value = bits_count(0b10000000 & tanks[0]) + bits_count(0b01111111 & tanks[0]) + bits_count(0b10000000 & tanks[1]) + bits_count(0b01111111 & tanks[1]);
  ws.textAll(value);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  //  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  //  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
  //    data[len] = 0;
  //    if (strcmp((char*)data, "toggle") == 0) {
  //      ledState = !ledState;
  //      notifyClients();
  //    }
  //  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {

  switch (type) {
    case WS_EVT_CONNECT:

      notifyClients();
      break;



  }

}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String& var) {
  Serial.println(var);
  if (var == "P_H") {
    String value = bits_count(0b10000000 & tanks[0]) + bits_count(0b01111111 & tanks[0]) + bits_count(0b10000000 & tanks[1]) + bits_count(0b01111111 & tanks[1]);
    return String(value);
  }
  return String();
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

void setup() {
  // Serial port for debugging purposes
  Serial.begin(300);
  WiFi.mode(WIFI_AP);
  // Connect to Wi-Fi
  WiFi.softAP(ssid, password);

  if (!MDNS.begin("tank")) {
    while (1) {
      delay(1000);
    }
  }
  if (!SPIFFS.begin()) {
    return;
  }
  MDNS.addService("http", "tcp", 80);
  dnsServer.setTTL(300);
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(DNS_PORT, "tank.net", WiFi.softAPIP());
  initWebSocket();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
  });

  server.on("/manifest.webmanifest", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "application/manifest+json", manifest);
  });

  server.on("/favicon512.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/favicon512.png", "image/png");
  });

  server.on("/favicon192.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/favicon192.png", "image/png");
  });

  // Start server
  server.begin();
}

void loop() {
  MDNS.update();
  dnsServer.processNextRequest();
  ws.cleanupClients();
  if (Serial.available() > 0) {
    Serial.readBytes(tanks, 2);
    notifyClients();
  }
}
