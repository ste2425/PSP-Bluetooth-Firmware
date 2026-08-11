#!/bin/sh

arduino-cli upload --input-dir build/ -b esp32-bluepad32:esp32:esp32 -p /dev/ttyUSB0