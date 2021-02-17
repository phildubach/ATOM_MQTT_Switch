# PlatformIO project for M5Stack ATOM lite to control a switch through MQTT 

This project is primarily intended for controlling a smart light or outlet
running Tasmota firmware through MQTT using an M5Stack ATOM lite. It should
be easily adaptable to other ESP32 platforms and MQTT environments.

To configure the code for your environment, copy the configuration template
in `include/config_template.h` to `include/config.h` and change the defines
to the settings required for your WiFi and MQTT server.
