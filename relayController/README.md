# Relay Controller

Control a basic relay - useful for mains-powered vibrators where speed control is not required, or for magnetic locks or similar for restraints.

| Device Details ||
|----------------|-|
| Device Type:   | On/Off |
| Tested Hardware: | [Wemos D1 Mini Relay Shield](https://www.wemos.cc/en/latest/d1_mini_shield/relay.html) |
| MQTT Publish Topic: | Configurable in code |
| MQTT On Message Payload: | {"state": 1} |
| MQTT Off Message Payload: | {"state": 0} |

**NOTE**: You will need to plug the relay shield into a D1 Mini controller, and then program the D1 Mini.  The shield on its own will not work without the controller.
