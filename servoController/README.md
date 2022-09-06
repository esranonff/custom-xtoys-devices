# Servo Controller

| Device Details ||
|----------------|------------|
| Device Type:   | Generic GPIO Server |
| Tested Hardware: | [WEMOS D1 Mini](https://www.wemos.cc/en/latest/d1/d1_mini.html) and standard metal gear servo |
| MQTT Publish Topic: | Configurable in code |
| MQTT Message Format: | {"angle" : &lt;&lt;INT&gt;&gt;, "step_delay": &lt;&lt;INT&gt;&gt; } |

`angle` is the target angle that you want the servo to rotate to.  `step_delay` is the number of seconds you want it to take to get there.

## WARNING

To confirm that this device is connected to WiFi and MQTT, the servo rotates between 0° and 90° repeatedly when first switched on.

***DO NOT CONNECT ANYTHING TO THE SERVO HORN BEFORE THE INITIALISATION IS COMPLETE OR YOU RUN THE RISK OF CAUSING INJURY***

Once the initialisation is complete, you can attach whatever devices/body-parts you wish and you will have proper control of them.
