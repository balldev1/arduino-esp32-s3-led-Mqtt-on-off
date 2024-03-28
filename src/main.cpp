#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// wifi
const char* ssid = "wirelessguru";
const char* pass = "guru54510250";

// MQTT Broker
const char* mqtt_server = "broker.mqtt.cool";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

// function.wifi
void setupWifi(){
  delay(100);
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  // connect.wifi
  WiFi.begin(ssid, pass);

  // !connect
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }

  // => conect.wifi
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Function to connect MQTT
void setupMqtt() {
  client.setServer(mqtt_server, mqtt_port);
}

// setup.wifi
void setup() {
  Serial.begin(115200); // เริ่มต้น Serial Monitor baud rate esp32 === 115200
  setupWifi(); // เชื่อมต่อ WiFi
  setupMqtt(); // เชื่อมต่อ Mqtt
}

// สั่งทำงาน 
void loop() {
  if (!client.connected()) {
    // wait connect
    Serial.println("Attempting MQTT connection...");
    // connect
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
    } else {
      // !connect
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
      return;
    }
  }
  
  client.loop();
  client.publish("topic", "hello");
  delay(5000);
}
