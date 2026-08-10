#!/bin/sh

# Update index of boards
arduino-cli core update-index --config-file ./arduino-cli.yaml

# install ESP32 board definition
arduino-cli core install esp32:esp32 --config-file ./arduino-cli.yaml

# install Bluepad32 board definition
arduino-cli core install esp32-bluepad32:esp32 --config-file ./arduino-cli.yaml