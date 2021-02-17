/* MIT License. Copyright (c) 2021 Phil Dubach */
#include <WiFi.h>
#include <ESPmDNS.h>
#include <MQTT.h>
#include <FastLED.h>

/* config.c should be copied from config_template.h in the
   include folder and changed to match the network setup */
#include "config.h"

#define BUTTON_GPIO 39
#define LED_GPIO 27
#define NUM_LEDS 1

WiFiClient wifiClient;
MQTTClient client;
CRGB led[NUM_LEDS];

void connect() {
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi");
    }
    MDNS.begin(CLIENT_ID);
    while (!client.connect(CLIENT_ID)) {
        delay(1000);
        Serial.println("Connecting to MQTT");
    }
    client.subscribe(SUBSCRIBE_TOPIC);
}

void onMessage(String &topic, String &payload) {
    Serial.println("incoming: " + topic + " - " + payload);
    if (payload == "ON") {
        led[0] = CRGB::Green;
    } else {
        led[0] = CRGB::Red;
    }
    FastLED.show();
}


void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_GPIO, INPUT_PULLUP);
    FastLED.addLeds<NEOPIXEL, LED_GPIO>(led, NUM_LEDS);
    FastLED.setBrightness(50);
    led[0] = CRGB::Blue;
    FastLED.show();
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    client.begin(MQTT_SERVER, wifiClient);
    client.onMessage(onMessage);
    connect();
}

void loop() {
    static int32_t buttonDownMS = 0;
    client.loop();
    if (!client.connected()) {
        connect();
    }
    if (digitalRead(BUTTON_GPIO)) {
        if (buttonDownMS == 0) {
            buttonDownMS = millis();
        }
    } else {
        if (buttonDownMS != 0) {
            if (millis() - buttonDownMS > 60) {
                // button was pressed
                client.publish(PUBLISH_TOPIC, "TOGGLE");
            }
            buttonDownMS = 0;
        }
    }
}
