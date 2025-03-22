#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define RELAY_PIN 15
#define led 2
#define MQTT_BROKER "192.168.1.200"
#define MQTT_TOPIC "sensor/pressure"
#define MAX 800000.0  // Set the threshold value for turning the relay ON/OFF
#define MIN 200000
#define WIFI_SSID "Dialog 4G 4EB"
#define WIFI_PASSWORD "Mang0s12"

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(115200);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);  // Relay OFF initially

    pinMode(led,OUTPUT);

    connectWiFi();
    client.setServer(MQTT_BROKER, 1883);
    client.setCallback(callback);

    reconnectMQTT();
    client.subscribe(MQTT_TOPIC);
}

void loop() {
    if (!client.connected()) {
        reconnectMQTT();
    }
    client.loop();
    digitalWrite(led,HIGH);
    delay(1000);
    digitalWrite(led,LOW);
    delay(1000);
}

void callback(char* topic, byte* payload, unsigned int length) {
    char message[length + 1];
    memcpy(message, payload, length);
    message[length] = '\0';
    
    float pressure = atof(message);
    Serial.print("Received Pressure: ");
    Serial.println(pressure);
    
    if (pressure > MAX) {
        digitalWrite(RELAY_PIN, HIGH);  // Relay ON
        Serial.println("Relay OFF");
    } else if(pressure < MIN) {
        digitalWrite(RELAY_PIN, LOW);  // Relay OFF
        Serial.println("Relay ON");
    }
}

void connectWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void reconnectMQTT() {
    while (!client.connected()) {
        Serial.println("Connecting to MQTT...");
        if (client.connect("ESP8266Subscriber")) {
            Serial.println("Connected to MQTT");
            client.subscribe(MQTT_TOPIC);
        } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" Trying again in 5 seconds...");
            delay(5000);
        }
    }
}

