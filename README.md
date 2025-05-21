# 🎂 BEAN-CAKE – Spy Bot on Wheels 🤖📷

**BEAN-CAKE** is a small, fast, and quiet spy robot that uses a high-speed coreless motor system and a live-streaming ESP32-S3-CAM to explore its surroundings! 
It is controlled via a remote that has two joysticks, a 4.0" TFT display, and real-time video feed.

---

##  Features

- Live video streaming from ESP32-S3-CAM
- Tank-style analog joystick control for precise speed and direction
- High-speed, quiet coreless motors
- 4.0" TFT color display on the controller
- Battery-powered & lightweight 
- 3D printed chassis and frame
- LED indicators, and toggle switches**


## Hardware Components


ESP32-S3-CAM - camera and bot brain
4.0" TFT ILI9341 - live camera stream + user input
2x Analog Joysticks Control - left/right (tank drive)
TB6612FNG Motor Driver
2x 7x16mm Coreless Motors
H31 3.7V LiPo Battery
LEDs, Switches, Bearings UI and mechanical support
*3D Printed Parts Track system, frame (bot + remote)



## 🛠️ FUNCTIONS

- The **ESP32-S3-CAM** streams MJPEG video via Wi-Fi.
- The **ESP32**:
  - Sends joystick input (PWM mapped) over UDP or HTTP.
  - Receives and displays the live video feed.
- The bot's **motor speed/direction** is based on joystick analog values.
- Everything is **fully wireless**, low-latency, and Arduino-compatible.

