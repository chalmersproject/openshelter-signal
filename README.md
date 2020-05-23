# Chalmers Signal Occupancy

## Rotary-Switch Branch
This branch is for chalmers signals that use the 12P rotary switches you can buy from creatron at College and Spadina. It expects 10K resistors between it's pins.

I'm just archiving this versions of the firmware in this branch to keep a copy for supporting legacy chalmers signals that have these rotary switches in them.

--- 

## This repo
This repository is for organization and work on the Chalmers-Signal-Occupancy device firmware.

## Quick Start
Setting up a development environment for this firmware is easiest with Platform IO.

## Hardware setup
![SPI display hookup diagram](https://raw.githubusercontent.com/akasoggybunz/Wemos-Mini-D1-with-1.44-TFT-LCD-ST7735-Driver/master/diagram.PNG)

## Hardware Used in this project
+ Some SPI or I2C cheap display
    - [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
    - [TFT + ESP8266 Library](https://github.com/lewisxhe/TFT_eSPI)
    - [pin hookup diagram](https://github.com/akasoggybunz/Wemos-Mini-D1-with-1.44-TFT-LCD-ST7735-Driver)
    - [Pertinant firmware example](https://github.com/lewisxhe/TFT_eSPI/blob/master/examples/320%20x%20240/weather-station/weather-station.ino)
+ A rotary encoder
+ A RGB LED ring (8 pixel probably)
+ Some ESP8266 board (prolly the WEMOS D1 Mini)
