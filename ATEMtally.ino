#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "ATEMclient.h"

#define PIN_RED (16)
#define PIN_GREEN (5)
#define PIN_CONNECT (4)

#define PIN_C0 (14)
#define PIN_C1 (12)
#define PIN_C2 (13)
 

ATEMclient AtemSwitcher;

// IP address of the ATEM Switcher
IPAddress switcherIp(192, 168, 10, 240);
// My Router SSID
const char* ssid = "MY SSID";
// My Router passwod
const char* password = "xxxxxxx";
 
int disconnect_count = 0;

WiFiClient client;

void setup() {
 pinMode(PIN_RED, OUTPUT);
 pinMode(PIN_GREEN, OUTPUT);
// pinMode(PIN_CONNECT, OUTPUT);
 pinMode(PIN_C0, INPUT);
 pinMode(PIN_C1, INPUT);
 pinMode(PIN_C2, INPUT);
 pinMode(15, INPUT);
 
 digitalWrite(PIN_RED, HIGH);
 digitalWrite(PIN_GREEN, HIGH);
// digitalWrite(PIN_CONNECT, HIGH);
  Serial.begin(115200);
  // Connect to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
   
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
   
  // Print the IP address
  Serial.println(WiFi.localIP());

  randomSeed(analogRead(5));  // For random port selection
    // Initialize a connection to the switcher:
  AtemSwitcher.begin(switcherIp);
  AtemSwitcher.serialOutput(0x82);
  AtemSwitcher.connect();
  
 digitalWrite(PIN_RED, LOW);
 digitalWrite(PIN_GREEN, LOW);
}
 
//************メインループ********************************
void loop() {
  AtemSwitcher.runLoop(10);
  if (AtemSwitcher.isConnected()) {
    int dimmer = digitalRead(15);
    int cam_no = digitalRead(PIN_C0) + digitalRead(PIN_C1) * 2 + digitalRead(PIN_C2) * 4;
    //Serial.print("cam_no=");
    //Serial.println(cam_no);
    
    if (AtemSwitcher.getProgramInputVideoSource(0) == cam_no){
      if (dimmer) {
        analogWrite(PIN_RED, 64);
      } else {
        analogWrite(PIN_RED, 0);
        digitalWrite(PIN_RED, HIGH);
      }
    } else {
      digitalWrite(PIN_RED, LOW);
    }
    if (AtemSwitcher.getPreviewInputVideoSource(0) == cam_no){
      if (dimmer) {
        analogWrite(PIN_GREEN, 64);
      } else {
        analogWrite(PIN_GREEN, 0);
        digitalWrite(PIN_GREEN, HIGH);
      }
    } else {
      digitalWrite(PIN_GREEN, LOW);
    }
  } else {
    if (disconnect_count < 20){
      Serial.println("Connection LOSS!A");
      digitalWrite(PIN_RED, LOW);
      digitalWrite(PIN_GREEN, HIGH);
    } else {
      Serial.println("Connection LOSS!B");
      digitalWrite(PIN_RED, HIGH);
      digitalWrite(PIN_GREEN, LOW);
    }
    disconnect_count++;
    if (disconnect_count > 40){
      disconnect_count = 0;
    }
  }

}
 
