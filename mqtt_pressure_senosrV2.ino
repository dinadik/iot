#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <HX711.h>  // HX711 library

// Pin definitions
#define DOUT_PIN 12  // HX711 Data pin
#define CLK_PIN 13   // HX711 Clock pin
#define led 2

// MQTT setup
#define MQTT_BROKER "192.168.1.200"
#define MQTT_TOPIC "sensor/pressure"
#define WIFI_SSID "Dialog 4G 4EB"
#define WIFI_PASSWORD "Mang0s12"

// HX711 setup
HX711 scale;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  // HX711 initialization
  scale.begin(DOUT_PIN, CLK_PIN);

  connectWiFi();
  client.setServer(MQTT_BROKER, 1883);
  pinMode(led,OUTPUT);
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }

  if (scale.is_ready()) {
    long raw_value = scale.get_units();   // Get raw pressure data
    float pressure = raw_value;  // Scale appropriately

    Serial.print("Pressure: ");
    Serial.println(pressure);

    char msg[10];
    dtostrf(pressure, 4, 2, msg);  // Convert float to string
    client.publish(MQTT_TOPIC, msg);
  } else {
    Serial.println("HX711 not ready...");
  }

  client.loop();
  delay(900);  // Publish every 5 seconds
  digitalWrite(led,HIGH);
  delay(100);
  digitalWrite(led,LOW);
  

}

// WiFi connection function
void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

// MQTT reconnect function
void reconnectMQTT() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266Publisher")) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Trying again in 5 seconds...");
      delay(5000);
    }
  }
}
