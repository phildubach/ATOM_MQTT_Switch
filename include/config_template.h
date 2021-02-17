/* MIT License. Copyright (c) 2021 Phil Dubach */
#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

/* WiFi configuration */
#define WIFI_SSID "SSID"
#define WIFI_PASS "PASS"

/* MQTT configuration */
#define MQTT_SERVER "192.168.86.85"
#define CLIENT_ID "OfficeSwitch"
#define SUBSCRIBE_TOPIC "tasmota/stat/OfficeLight/POWER"
#define PUBLISH_TOPIC "tasmota/cmnd/OfficeLight/POWER"

#endif /* INC_CONFIG_H_ */
