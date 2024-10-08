# MultiI2CDevices

## Overview
This repository contains scripts for interfacing with multiple I2C devices. It includes scripts for using multiple VL53L0X Time-of-Flight (ToF) sensors as well as MPU6050 sensors.

demo video:[![WhatsApp Image 2024-05-05 at 18 29 51_886df5ed](https://github.com/Ashutoshss/MultiI2CDevices/assets/103228643/9d244de2-422c-45a3-a185-540dd8abfc97)
](https://youtu.be/zLPeTh2IeD8?si=r3Zhy_QrlO2PhxwH)

## Dependencies
The scripts in this repository depend on the Adafruit VL53L0X library and the Adafruit MPU6050 library. Make sure to install those libraries before running the scripts.

## Scripts
1. **MultiVL53L0X.ino**: This script allows you to interface with three VL53L0X ToF sensors using I2C communication.
2. **MultiI2CDevices.ino**: This script allows you to interface with an MPU6050 sensor and three VL53L0X ToF sensors using I2C communication.

## Usage
Upload the scripts to your microcontroller. Make sure to connect the sensors to the correct pins as defined in the scripts especially XSHUT pins.
I will definately add more stuff to this repo in context of I2C Communication use topic.

## Installation
The Adafruit libraries can be installed through the Arduino IDE's Library Manager. Navigate to Sketch > Include Library > Manage Libraries, then search for and install the "Adafruit_VL53L0X" and "Adafruit MPU6050" libraries.
