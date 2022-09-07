# Servo Controller

## WARNING

To confirm that this device is connected to WiFi and MQTT, the servo rotates between 0° and 90° repeatedly when first switched on.

***DO NOT CONNECT ANYTHING TO THE SERVO HORN BEFORE THE INITIALISATION IS COMPLETE OR YOU RUN THE RISK OF CAUSING INJURY***

Once the initialisation is complete, you can attach whatever devices/body-parts you wish and you will have proper control of them.

## Using the device

| Device Details ||
|----------------|------------|
| Device Type:   | Generic GPIO Server |
| Tested Hardware: | [WEMOS D1 Mini](https://www.wemos.cc/en/latest/d1/d1_mini.html) and standard metal gear servo connected to port **D1** |
| MQTT Publish Topic: | Configurable in code |
| MQTT Message Format: | {"angle" : &lt;&lt;INT&gt;&gt;, "step_delay": &lt;&lt;INT&gt;&gt; } |

`angle` is the target angle that you want the servo to rotate to.  `step_delay` is the number of seconds you want it to take to get there.

### XToys configuration

Unlike the other devices in this repository, the Servo Controller relies on the "Generic Custom Toy" component.

Once you have created your custom toy in the XToys interface, you then need to add it to a script.

A [sample script](https://xtoys.app/scripts/-NBIHwjRoteqkl3Ra04e) is available within XToys to provide a guide to basic control.
