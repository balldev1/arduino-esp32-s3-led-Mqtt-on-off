#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// wifi
const char* ssid = "wirelessguru";
const char* pass = "guru54510250";
const int LED_Pin_1 = 2; // กำหนดขา LED_Pin_1 เป็นขาที่ 2
const int LED_Pin_2 = 3; // กำหนดขา LED_Pin_2 เป็นขาที่ 3
const int LED_Pin_3 = 4; // กำหนดขา LED_Pin_3 เป็นขาที่ 4
// MQTT Broker
const char* mqtt_server = "broker.mqtt.cool";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

// Function to connect WiFi
void setupWifi() {
  delay(100);
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Function to connect MQTT
void setupMqtt() {
  client.setServer(mqtt_server, mqtt_port);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  // Check if the topic is "test/led" and payload is "off"
  if (strcmp(topic, "test/led") == 0 && strncmp((char*)payload, "off", length) == 0) {
    // Turn off all pins
    for (int pin = 0; pin <= 39; pin++) {
      pinMode(pin, OUTPUT);
    }

    // Turn on all pins
    // for (int pin = 0; pin <= 39; pin++) {
    //   digitalWrite(pin, LOW); // HIGH
    // }

    delay(1000);
  } else {
    // Send message to terminal
    Serial.println("error");
  }
}

// logic ให้ไฟติด
// Callback function for MQTT messages
// void callback(char* topic, byte* payload, unsigned int length) {
  
//   Serial.print("Message arrived [");
//   Serial.print(topic);
//   Serial.print("] ");
//     // Set all pins as OUTPUT
//     for (int pin = 0; pin <= 39; pin++) {
//       pinMode(pin, OUTPUT);
//     }

//     // Turn on all pins
//     for (int pin = 0; pin <= 39; pin++) {
//       digitalWrite(pin, HIGH); 
//     }

//     delay(1000); // Wait for 1 second

//     // // Turn off all pins
//     // for (int pin = 0; pin <= 39; pin++) {
//     //   digitalWrite(pin, LOW);
//     // }
// }

// Reconnect to MQTT broker
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      client.publish("topic","MQTT Server is connected");
      client.subscribe("test/led");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}


// Setup function
void setup() {
  Serial.begin(115200);
  setupWifi();
  setupMqtt();
  client.setCallback(callback);
  // ไฟติดเมือเปิด
  pinMode(LED_Pin_1, OUTPUT);
  pinMode(LED_Pin_2, OUTPUT);
  pinMode(LED_Pin_3, OUTPUT);
}

// Loop function
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
