#include <Arduino.h>
#include <Wire.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif


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

// Create the JSON Document to be sent to the xtoys server
DynamicJsonDocument doc(96); // https://arduinojson.org/v6/assistant/

unsigned long lastMsg = 0;

#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];

WiFiClientSecure espClient;   // for no secure connection use WiFiClient instead of WiFiClientSecure
PubSubClient client(espClient);

int gsr_high = 0;
int gsr_low = 2000;

// Setup the GSR sensor
const int GSR=A0;
int sensorValue=0;
int gsr_average=0;

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
  }
  randomSeed(micros());
  Serial.println("\nWiFi connected\nIP address: ");
  Serial.println(WiFi.localIP());
  analogWrite(4, 0);
  analogWrite(5, 0);
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
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");   // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void update_gsr(){
      long sum=0;
  for(int i=0;i<10;i++)           //Average the 10 measurements to remove the glitch
      {
      sensorValue=analogRead(GSR);
      sum += sensorValue;
      delay(5);
      }
    gsr_average = sum/10;
    if ( gsr_average > gsr_high){
        gsr_high = gsr_average;
    }
    if ( gsr_average < gsr_low ){
        gsr_low = gsr_average;
    }
    // send data
    //doc["key"] = "sensors/gsr";
    doc["gsr"]["gsr_high"] = gsr_high;
    doc["gsr"]["gsr_low"] =  gsr_low;
    doc["gsr"]["gsr_avg"] = gsr_average;
    char payload[256];
    serializeJson(doc, payload);
    //itoa(gsr_average, payload, 10);
    Serial.print(payload);
    Serial.println(); // send newline
    client.publish(xtoys_topic, payload);
}
//================================================ setup
//================================================
void setup() {
  Serial.begin(9600);
  while (!Serial) delay(1);
  setup_wifi();

  #ifdef ESP8266
    espClient.setInsecure();
  #else   // for the ESP32
    espClient.setCACert(root_ca);      // enable this line and the the "certificate" code for secure connection
  #endif

  client.setServer(mqtt_server, mqtt_port);
}


//================================================ loop
//================================================
void loop() {

  if (!client.connected()) reconnect();
  update_gsr();
  delay(500);

}
