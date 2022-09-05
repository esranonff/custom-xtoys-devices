#include <Arduino.h>
#include <Wire.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

int relay_pin = D1;

#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

// Set your WiFi details here
const char *ssid     = "<MY WIFI ID>";
const char *password = "<MY WIFI PASSWORD>";

const char* mqtt_server = "<MY MQTT SERVER>"; //mqtt server
const char* mqtt_username = "<MY MQTT USERNAME>"; //mqtt Username
const char* mqtt_password = "<MY MQTT PASSWORD>"; //mqtt password

// If your MQTT server does *NOT* listen on port 8883, change this here
const int mqtt_port =8883;

// Set this to the same value as the settings you created in XToys.
// 
// As an example, this could be "toys/genitals" and then you
// create another device that has a topic of "toys/nipples", 
// or you can be even more generic with a topic of "toy1".
//
// As long as the values match here and in xtoys, this should work!
const char* xtoys_topic="<MY XTOYS MQTT TOPIC>";

int pulse_during_setup_state = 0;

unsigned long lastMsg = 0;

#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];

WiFiClientSecure espClient;   // for no secure connection use WiFiClient instead of WiFiClientSecure
PubSubClient client(espClient);

// Pulse the relay during startup so we know the connections are working
// without needing to check the logs.
//
// You wil get one pulse for each connection attempt of the WiFi
// followed by one long, four short, and one long pulse once the
// connection is established to the MQTT server.
void pulse_during_setup() {
    if (pulse_during_setup_state == 0){
//        Serial.println("Onboard LED state was HIGH, switching to LOW");
        pulse_during_setup_state = 1;
        digitalWrite(relay_pin, LOW);
    }
    else if (pulse_during_setup_state == 1) {
//        Serial.println("Onboard LED state was LOW, switching to HIGH");
        pulse_during_setup_state = 0;
        digitalWrite(relay_pin, HIGH);
        
    }
}
//==========================================
void setup_wifi() {
  delay(10);
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    pulse_during_setup();
  }
  randomSeed(micros());
  Serial.println("\nWiFi connected\nIP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(relay_pin, LOW);
  
}


//=====================================
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";   // Create a random client ID
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");

      // pulse multiple times to show that WiFi is connected
      digitalWrite(relay_pin, LOW);
      
      delay(1000);
      digitalWrite(relay_pin, HIGH);
      
      delay(300);
      digitalWrite(relay_pin, LOW);
      
      delay(300);
      digitalWrite(relay_pin, HIGH);
      
      delay(300);
      digitalWrite(relay_pin, LOW);
      
      delay(300);
      digitalWrite(relay_pin, HIGH);
      
      delay(300);
      digitalWrite(relay_pin, LOW);
      
      delay(300);
      digitalWrite(relay_pin, HIGH);
      
      delay(300);
      digitalWrite(relay_pin, LOW);
      
      delay(1000);
      digitalWrite(relay_pin, HIGH);

      delay(300);
      digitalWrite(relay_pin, LOW);
      


      client.subscribe(xtoys_topic);   // subscribe the topics here
      //client.subscribe(command2_topic);   // subscribe the topics here
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");   // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

//=======================================
// This void is called every time we have a message from the broker

void callback(char* topic, byte* payload, unsigned int length) {
  StaticJsonDocument<256> doc;
  deserializeJson(doc, payload, length);
  if (doc["state"] == 1) {
      Serial.println("Locked");
      digitalWrite(relay_pin, HIGH);
  }
  else {
      Serial.println("Unlocked");
      digitalWrite(relay_pin, LOW);
  }
}
//================================================ setup
//================================================
void setup() {
  Serial.begin(9600);
  pinMode(relay_pin, OUTPUT);
  while (!Serial) delay(1);
  setup_wifi();

  #ifdef ESP8266
    espClient.setInsecure();
  #else   // for the ESP32
    espClient.setCACert(root_ca);      // enable this line and the the "certificate" code for secure connection
  #endif

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}


//================================================ loop
//================================================
void loop() {

  if (!client.connected()) reconnect();
  client.loop();

}
