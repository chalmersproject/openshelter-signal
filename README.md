# Chalmers Signal Occupancy

This repository is for organization and work on the Chalmers Signal Occupancy device firmware.

## Quick Start

Setting up a development environment for this firmware is easiest with Platform IO.

## Hardware Used in this project

| Part Type                                    | Model Number                                                                                                                                                                                                                                                                                                                                                                                                   | Seller                                                                                                                    | Link                                                                                   | Picture                              |
| -------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------- | ------------------------------------ |
| TFT Display                                  | [1.44 Inch TFT LCD 65K Color 128x128 Display Screen SPI Serial Port Module ST7735 for 51 ARM Arduino](https://www.aliexpress.com/item/1-44-Inch-TFT-LCD-65K-Color-128x128-Display-Screen-SPI-Serial-Port-Module-ST7735-for/33014277663.html "1.44 Inch TFT LCD 65K Color 128x128 Display Screen SPI Serial Port Module ST7735 for 51 ARM Arduino")                                                             | [DIY More Alice1101983 Store (AliExpress)](https://www.aliexpress.com/store/2178016?spm=a2g0s.9042647.0.0.7ff24c4dD8jpYV) | https://www.aliexpress.com/item/33014277663.html?spm=a2g0s.12269583.0.0.5f7713304vjAGt | ![](https://i.imgur.com/9U5iU5Z.png) |
| ESP8266 Microcontroller development board    | [diymore ESP8266 ESP-12E ESP-12F CH340 CH340G for Arduino WeMos D1 Mini WIFI Wireless Development Module D1 Mini NodeMCU IOT](https://www.aliexpress.com/item/diymore-ESP8266-ESP-12E-ESP-12F-CH340-CH340G-for-Arduino-WeMos-D1-Mini-WIFI-Wireless-Development/32975485449.html "diymore ESP8266 ESP-12E ESP-12F CH340 CH340G for Arduino WeMos D1 Mini WIFI Wireless Development Module D1 Mini NodeMCU IOT") | [DIY More Alice1101983 Store (AliExpress)](https://www.aliexpress.com/store/2178016?spm=a2g0s.9042647.0.0.7ff24c4dD8jpYV) | https://www.aliexpress.com/item/32975485449.html?spm=a2g0s.9042311.0.0.5fda4c4dbZOZGj  | ![](https://i.imgur.com/zQkQXjP.png) |
| WS2812 RGB Individually Addressable LED Ring | [diymore WS2812 5050 RGB LED Ring Lamp Light 7 Bits LEDs with Integrated Driver for Arduino](https://www.aliexpress.com/item/diymore-WS2812-5050-RGB-LED-Ring-Lamp-Light-7-Bits-LEDs-with-Integrated-Driver-for-Arduino/32668340327.html?spm=a2g0s.9042311.0.0.5fda4c4dbZOZGj "diymore WS2812 5050 RGB LED Ring Lamp Light 7 Bits LEDs with Integrated Driver for Arduino")                                    | [DIY More Alice1101983 Store (AliExpress)](https://www.aliexpress.com/store/2178016?spm=a2g0s.9042647.0.0.7ff24c4dD8jpYV) | https://www.aliexpress.com/item/32668340327.html?spm=a2g0s.9042311.0.0.5fda4c4dbZOZGj  | ![](https://i.imgur.com/8jlq77c.png) |
| Rotary Encoder                               | [Rotary Encoder Module 5V Brick Sensor Development Round Audio Rotating Potentiometer Knob Cap for Arduino](https://www.aliexpress.com/item/Rotary-Encoder-Module-5V-Brick-Sensor-Development-Round-Audio-Rotating-Potentiometer-Knob-Cap-for-Arduino/32908505224.html "Rotary Encoder Module 5V Brick Sensor Development Round Audio Rotating Potentiometer Knob Cap for Arduino")                            | [DIY More Alice1101983 Store (AliExpress)](https://www.aliexpress.com/store/2178016?spm=a2g0s.9042647.0.0.7ff24c4dD8jpYV) | https://www.aliexpress.com/item/32908505224.html?spm=a2g0s.9042311.0.0.5fda4c4dbZOZGj  | ![](https://i.imgur.com/urflyU1.png) |

## Pin Bindings

![ WMOS D1 Mini ](https://i2.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/05/ESP8266-WeMos-D1-Mini-pinout-gpio-pin.png?w=715&quality=100&strip=all&ssl=1)

### TFT Display

| D1 Mini     | Shield  | Other Shield     |
| ----------- | ------- | ---------------- |
| RST         | TFT_RST | RES              |
| D0 [GPIO16] | TFT_DC  | DC (or A0 or RS) |
| D4          | TFT_CS  |                  |
| D7          | MOSI    | SDA              |
| D5          | SCK     | SCL              |
| Unused      | ---     | BL               |
| 3v          | TFT_LED | VCC              |
| GND         | GND     | GND              |

### Rotary Encoder

| Encoder Pin  | Wemos Pin [GPIO number] | Purpose         |
| ------------ | ----------------------- | --------------- |
| S1           | D1 [GPIO5]              | input clock     |
| S2           | D2 [GPIO4]              | Input DT        |
| Key (button) | D3 [GPIO0]              | Click-In Button |
| VCC          | 3v                      | power (derr)    |
| GND          | GND                     | ground (derr)   |

### LED Ring

| Wemos D1 Mini Pin | digital RGB LED Pin |
| ----------------- | ------------------- |
| GPIO15 / D8       | DIN                 |
| 3v                | VCC                 |
| GND               | GND                 |
