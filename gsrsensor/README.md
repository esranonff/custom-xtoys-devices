# Galvanic Skin Response Sensor

| Device Details ||
|----------------|------------|
| Device Type:   | 2 channel vibrator |
| Tested Hardware: | [Wemos D1 Mini](https://www.wemos.cc/en/latest/d1/d1_mini.html) connected to a [Grove GSR sensor](https://wiki.seeedstudio.com/Grove-GSR_Sensor/) via pin `A0` |
| MQTT Publish Topic: | Configurable in code |
| MQTT Message Format: | {"gsr":{"gsr_high":<INT>,"gsr_low":<INT>,"gsr_avg":<INT>}} |

`gsr_high` is the highest measurement registered since the D1 was powered on, `gsr_low` is the lowest measurement since the D1 was powered on, and `gsr_avg` is the average GSR over the past minute.

A "high" reading signifies a low arousal level, whereas a low reading signifies a high level of arousal.
