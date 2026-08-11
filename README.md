# PSP Bluetooth Firmware

---

⚠️ **AI and stuff** This ReadME was written with AI based on the code base because im lazy and dont like writing documentation. 

Iv'e at least read it.

---

This firmware turns an ESP32 module into a bridge between a PSP and Bluetooth controllers. It uses the BluePad32 library and communicates with the PSP over Serial2.

This project is part of the PSP Bluetooth ecosystem. More information about the wider project is available at https://github.com/psp-bluetooth.

## Overview

The firmware exposes a small serial command protocol that the PSP can use to:

- query controller state
- disconnect controllers
- change LED and vibration settings
- enable or disable new Bluetooth pairings
- retrieve firmware version information

The serial link uses Serial2 with the following pins:

| Signal | GPIO |
| --- | --- |
| RX | 18 |
| TX | 16 |

The firmware runs at 115200 baud.

## Building and uploading

This project now uses Arduino CLI rather than PlatformIO. The only required dependency for a user is Arduino CLI itself. The build scripts handle the board package installation for you.

### Prerequisites

Install Arduino CLI and ensure it is available on your PATH.

### Quick start

From the repository root, run:

```bash
./setup.sh
./compile.sh
./upload.sh
```

### What the scripts do

- `setup.sh` updates the board index and installs the ESP32 and BluePad32 board packages using the configuration in `arduino-cli.yaml`.
- `compile.sh` builds the firmware for the `esp32-bluepad32:esp32:esp32` board.
- `upload.sh` uploads the built firmware to `/dev/ttyUSB0`.

If your ESP32 is connected to a different device, update the port in `upload.sh` before running it.

## Acknowledgements

The work here builds on earlier contributions from several people and projects.

- TokyoDrift - early work using the PSP SIO port to relay controller input.
- OPDitto - work that helped with SIO handling and analog stick support.
- X41 - shared an early working SIO hello-world example that helped get the hardware working.
- PSP Homebrew Discord - a source of guidance and troubleshooting help.

---

## Developer notes

### Command protocol

The PSP sends a single command byte to the ESP32. The firmware then reads any additional request bytes required by that command and replies with either:

- a status byte only, or
- a status byte followed by payload bytes

If an error status byte is returned, no further data follows.

### Error status bytes

- `0x0A` - request data was not received
- `0x0B` - controller was not found or is not connected
- `0x17` - command was not recognized

### Command reference

| Command byte | Description | Request bytes | Response bytes |
| --- | --- | --- | --- |
| `0x02` | Ping | None | `0x10` |
| `0x03` | Request controller data | `[controllerIndex]` | `0x0C`, `<analogRX>`, `<analogRY>`, `<analogLX>`, `<analogLY>`, `<dpad>`, `<buttonsHigh>`, `<buttonsLow>`, `<miscHigh>`, `<miscLow>` |
| `0x04` | Enable new connections | None | `0x11` |
| `0x05` | Disable new connections | None | `0x12` |
| `0x06` | Disconnect controller | `[controllerIndex]` | `0x13` |
| `0x07` | Set controller LED colour | `[controllerIndex, red, green, blue]` | `0x0D` |
| `0x08` | Set controller vibration | `[controllerIndex, delayLow, delayHigh, durationLow, durationHigh, weakMagnitude, strongMagnitude]` | `0x0E` |
| `0x09` | Get controller information | `[controllerIndex]` | `0x0F`, `<controllerType>`, `<batteryLevel>` |
| `0x0A` | Forget Bluetooth keys | None | `0x14` |
| `0x0B` | Set player LEDs | `[controllerIndex, playerNumber]` | `0x15` |
| `0x0C` | Get firmware version | None | `0x16`, `<length>`, `<versionString>` |

### Response byte reference

- `0x0C` - controller data response
- `0x0D` - LED update accepted
- `0x0E` - vibration update accepted
- `0x0F` - controller info response
- `0x10` - ping response
- `0x11` - new connections enabled
- `0x12` - new connections disabled
- `0x13` - controller disconnected
- `0x14` - Bluetooth keys forgotten
- `0x15` - player LED update accepted
- `0x16` - firmware version response
- `0x17` - command not found

### Button and LED bit masks

The state bytes returned by controller data use bitmasks for button and LED state.

| Mask value | Meaning |
| --- | --- |
| `0x01` | D-pad up |
| `0x02` | D-pad down |
| `0x04` | D-pad left |
| `0x08` | D-pad right |
| `0x01` | Cross |
| `0x02` | Circle |
| `0x04` | Square |
| `0x08` | Triangle |
| `0x10` | L1 |
| `0x20` | R1 |
| `0x40` | L2 |
| `0x80` | R2 |
| `0x100` | L3 |
| `0x200` | R3 |
| `0x01` | System |
| `0x02` | Capture |
| `0x04` | Start |
| `0x08` | Select |
| `0x01` | Player 1 LED |
| `0x02` | Player 2 LED |
| `0x04` | Player 3 LED |
| `0x08` | Player 4 LED |

The currently hardcoded firmware version string exposed by the firmware is `v1.0.0`.

