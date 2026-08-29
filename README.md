Ultrasonic automatic-braking RC car built with Arduino, PWM motor control, and distance-based speed zones for real-time obstacle avoidance and stopping.
Recycled an old RC car's chassis and used a motor controlled by the Arduino to directly control the rear axle using gears. A video of the project is under the "demovideo" file. 

## How It Works

The ultrasonic sensor is mounted at the front of the car and continuously measures the distance to objects ahead.

The Arduino repeatedly:

1. Sends a trigger pulse to the HC-SR04.
2. Measures the duration of the returning echo.
3. Converts the echo time into distance.
4. Compares the measured distance against several distance thresholds.
5. Selects an appropriate motor PWM value.
6. Sends the PWM signal to a transistor that controls the DC drive motor.

The system uses multiple speed zones rather than immediately switching between full speed and stop.

Example control logic:

| Distance | Motor Command |
| --- | --- |
| Greater than 50 cm | Full speed |
| 30–50 cm | Medium speed |
| 10–30 cm | Reduced speed |
| 10 cm or less | Stop |

PWM values are used to vary the motor speed.

Typical values in the current program are:

- 255 — full speed
- 170 — medium speed
- 140 — slow speed
- 0 — stopped

## Hysteresis

A small hysteresis system is used to prevent the motor from rapidly switching between moving and stopping when the sensor reading fluctuates near the stopping threshold.

The car stops when the obstacle reaches approximately:

`10 cm`

After stopping, it does not begin moving again until the obstacle is farther than:

`15 cm`

This prevents behavior such as:

`MOVE → STOP → MOVE → STOP`

when ultrasonic measurements vary slightly around the stopping distance.

## Sensor Failure Handling

The ultrasonic measurement uses a timeout.

If no valid echo is detected, the distance function returns an invalid value instead of assuming that the path is clear.

The Arduino responds by stopping the motor.

This prevents a failed sensor reading from causing the vehicle to accelerate.

## Motor Control

The Arduino does not power the DC motor directly.

Instead, Arduino pin D9 sends a low-current PWM control signal through a resistor to a 2N2222A NPN transistor.

The transistor acts as an electronic switch that controls the larger current required by the motor.

A flyback diode is connected across the motor to protect the transistor and other electronics from voltage spikes generated when the motor is switched off.

## Parts List

- Arduino Uno R3
- HC-SR04 ultrasonic distance sensor
- DC geared motor
- RC car chassis and wheels
- 2N2222A NPN transistor
- 1 kΩ resistor
- Rectifier diode / flyback diode
- Breadboard
- Breadboard power supply module
- External battery
- Jumper wires

## Pin Connections

| Component | Arduino Pin |
| --- | --- |
| Motor control | D9 |
| HC-SR04 TRIG | D10 |
| HC-SR04 ECHO | D11 |
| HC-SR04 VCC | 5V |
| HC-SR04 GND | GND |

The Arduino, sensor, motor circuit, and external power supply share a common ground.

## Motor Driver Circuit

The motor circuit follows this general structure:

`Power Supply → Motor → Transistor → Ground`

Arduino D9 controls the transistor through a 1 kΩ resistor.

The flyback diode is connected in parallel with the motor, with the striped side toward the positive supply.

## Distance Measurement

The HC-SR04 determines distance by measuring the round-trip travel time of an ultrasonic pulse.

The Arduino calculates:

`distance = duration × 0.034 / 2`

where:

- `duration` is the echo pulse length in microseconds
- `0.034 cm/µs` approximates the speed of sound
- `/2` accounts for the outgoing and returning path of the sound wave

## What I Learned

This project helped me develop experience with:

- Arduino programming
- Ultrasonic sensors
- PWM motor control
- Transistor switching
- DC motors
- Flyback protection
- Breadboard circuit design
- External power supplies
- Common-ground circuits
- Conditional control logic
- Hysteresis
- Sensor failure handling
- Hardware and software debugging

## Future Improvements

Possible future improvements include:

- Calculating obstacle closing speed
- Dynamic braking based on vehicle velocity
- Multiple ultrasonic sensors
- Steering control
- H-bridge motor control
- Reverse functionality
- Sensor filtering and averaging
- Improved battery and power-management system
