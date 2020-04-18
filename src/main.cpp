#ifndef UNIT_TEST

#include <Arduino.h>

#endif

#include <DNSServer.h>
#include <WiFiManager.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <IRremoteESP8266.h>
#include <IRsend.h>

#include <ArduinoJson.h>

// TODO: Make button to reset wifi
// TODO: Add more devices

/*********************************************************************/

// LG TV IR code
#define TV_ON  0x20DF10EF
#define TV_INPUT 0x20DFD02F
#define TV_VOL_UP 0x20DF40BF
#define TV_VOL_DOWN 0x20DFC03F
#define TV_VOL_MUTE 0x20DF906F
#define TV_PROG_UP 0x20DF00FF
#define TV_PROG_DOWN 0x20DF807F
#define TV_ARROW_UP 0x20DF02FD
#define TV_ARROW_DOWN 0x20DF827D
#define TV_ARROW_LEFT 0x20DFE01F
#define TV_ARROW_RIGHT 0x20DF609F
#define TV_OK 0x20DF22DD
#define TV_SETTINGS 0x20DFC23D
#define TV_BACK 0x20DF14EB

/*********************************************************************/

ESP8266WebServer server(80);

IRsend irsend(14);  // IR LED is controlled by GPIO 14 (D5)

String last_input_selected = "aux";
String last_eq_selected = "music";

/*********************************************************************/

/**
 * Send response
 * 
 * @param html_code HTML status code
 * @param message 
 */
void sendResponse(int html_code, String message) {
    String body;
    DynamicJsonDocument raw_body(1024);

    raw_body["msg"] = message;

    serializeJson(raw_body, body);

    server.send(html_code, "text/json", body);
}

/**
 * Send the command to the TV
 * @param arg is the command received
 */
bool sendAction(String arg) {
    if (arg == "on") {
        irsend.sendNEC(TV_ON, 32);
    } else if (arg == "input") {
        irsend.sendNEC(TV_INPUT, 32);
    } else if (arg == "vol_up") {
        irsend.sendNEC(TV_VOL_UP, 32);
    } else if (arg == "vol_down") {
        irsend.sendNEC(TV_VOL_DOWN, 32);
    } else if (arg == "vol_mute") {
        irsend.sendNEC(TV_VOL_MUTE, 32);
    } else if (arg == "prog_up") {
        irsend.sendNEC(TV_PROG_UP, 32);
    } else if (arg == "prog_down") {
        irsend.sendNEC(TV_PROG_DOWN, 32);
    } else if (arg == "arrow_up") {
        irsend.sendNEC(TV_ARROW_UP, 32);
    } else if (arg == "arrow_down") {
        irsend.sendNEC(TV_ARROW_DOWN, 32);
    } else if (arg == "arrow_left") {
        irsend.sendNEC(TV_ARROW_LEFT, 32);
    } else if (arg == "arrow_right") {
        irsend.sendNEC(TV_ARROW_RIGHT, 32);
    } else if (arg == "ok") {
        irsend.sendNEC(TV_OK, 32);
    } else if (arg == "settings") {
        irsend.sendNEC(TV_SETTINGS, 32);
    } else if (arg == "back") {
        irsend.sendNEC(TV_BACK, 32);
    } else {
      return false;
    }
    
    return true;
}

/**
 * Check the command received for the TV
 */
void checkArgs() {
    int html_code;
    String message = "";
    
    bool res;

    DynamicJsonDocument body(1024);

    if (server.hasArg("plain") == false) {
        html_code = 400;
        message = "Body not found";
    } else {
      deserializeJson(body, server.arg("plain"));

      String action = body["action"];
      
      res = sendAction(action);
      
      if (res) {
        html_code = 200;
        message = "Successful action";
      } else {
        html_code = 400;
        message = "Action not found";
      }
    }

    sendResponse(html_code, message);
}

/*********************************************************************/

void setup() {
  Serial.begin(9600);
  
  irsend.begin();
  
  // WiFiManager
  WiFiManager wifiManager;

  // Reset settings - for testing
  // wifiManager.resetSettings();

  wifiManager.setTimeout(180);
  wifiManager.setHostname("ESP_RemoteController");
  
  if(!wifiManager.autoConnect("ESP_RemoteController - Access Poinit")) {
    Serial.println("Failed to connect and hit timeout");
    delay(3000);
    
    ESP.reset();
    delay(5000);
  } 

  Serial.println("Connected");

  server.on("/rc", checkArgs);

  server.begin(); 
}

void loop() {
  server.handleClient();
}