#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define LED_PIN 25
#define PHOTORESISTOR_PIN 34
#define THERMOMETER_PIN 35

#include "garden-sensorboard/device/Device.h"
#include "garden-sensorboard/device/DeviceBuilder.h"

#include "iot/sensor/photoresistor/Photoresistor.h"

const char* ssid = "Home&Life SuperWiFi-5D91";
const char* password = "7RR7UY3DG7XT8KMQ";
const char* mqtt_server = "192.168.1.49";
WiFiClient wifi;
PubSubClient mqtt(wifi);

DeviceBuilder* builder = new DeviceBuilder();
Device* device = builder
->withDigitalLed(new DigitalLed(LED_PIN))
->withPhotoresistor(new Photoresistor(PHOTORESISTOR_PIN))
->withThermometer(new Thermometer(THERMOMETER_PIN))
->build();

void setup_wifi() {
    delay(10);

    Serial.println(String("Connecting to ") + ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnect() {
  
  // Loop until we're reconnected
  
  while (!mqtt.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // Create a random client ID
    String clientId = String("esiot-2122-client-")+String(random(0xffff), HEX);

    // Attempt to connect
    if (mqtt.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // client.publish("outTopic", "hello world");
      // ... and resubscribe
      mqtt.subscribe("esiot-2122");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.println(length);
}

void setup(){
    Serial.begin(115200);

    setup_wifi();
    randomSeed(micros());
    mqtt.setServer(mqtt_server, 1883);
    mqtt.setCallback(callback);

    device->setup();
}


unsigned long lastMsgTime = 0;
void loop() {
    if (!mqtt.connected()) {
        reconnect();
    }
    mqtt.loop();

    unsigned long now = millis();
    if (now - lastMsgTime > 1000) {
        lastMsgTime = now;
        device->computeRead();

        mqtt.publish("smart-garden/light", String(device->getPhotoresistor()->getLight()).c_str());

        mqtt.publish("smart-garden/temperature", String(device->getThermometer()->getTemperature()).c_str());
    }
}
