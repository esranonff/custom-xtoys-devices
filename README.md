# XToys.app Custom Toys

This repo contains code for various types of device using the [XToys](https://xtoys.app) custom integrations.

## What kind of devices will it run on?

The code is designed to run on either ESP8266 or ESP32 devices, and links to example boards are include in the repository of each device.

## How do I upload the code to my device?

All the code has been written to work via the [PlatformIO](https://platformio.org) development platform, and as a result the compilation/deployment should be as easy as plugging in the device via USB, updating the WiFi and MQTT Username/Password, and either using the GUI or running the following commands:

   * poetry install
   * poetry run pio run -t upload

As long as your credentials are correct, you should see the messages on the serial console as the device connects first to WiFi then to MQTT.

## Where do I get an MQTT Connection from?

I use [HiveMQ Cloud](https://www.hivemq.com/mqtt-cloud-broker/) for my projects.  It's free and stable.

If you don't want to use a public platform, and you know what you are doing, you could install and run an MQTT Broker on the cloud provider of your choice or expose it from your home network, but I'd strongly recommend the HiveMQ route and I can't provide support on the MQTT Broker configuration.
