# Motor Controller

| Device Details ||
|----------------|------------|
| Device Type:   | 2 channel vibrator |
| Tested Hardware: | [MCU ESP8266 Development Board with Motor Driver](https://www.amazon.co.uk/gp/product/B07ZCMZW9Q) |
| MQTT Publish Topic: | Configurable in code |
| MQTT Message Format: | {"channel" : &lt;&lt;channel&gt;&gt;, "speed": &lt;&lt;vibrate&gt;&gt; } |

Channel `1` is Motor A, Channel `2` is Motor B, max speed is 100, min speed is 0.
