#pragma once

#include <Arduino.h>

#include "../Serial.h"
#include "../controllerManager.h"

using CommandFunction = void (*)();

struct Command
{
    uint8_t code;
    CommandFunction function;
};

// Command implementations
void controllerDataExecute();
void pingExecute();
void enableNewConnectionsExecute();
void disableNewConnectionsExecute();
void disconnectControllerExecute();
void forgetBluetoothKeysExecute();
void controllerLEDExecute();
void controllerVibrateExecute();
void controllerInfoExecute();
void controllerPlayerLEDExecute();
void firmwareVersionExecute();

// Command registry
extern const Command commands[];
extern const size_t commandCount;

#define DATA_NOT_RECIEVED 0xA
#define CONTROLLER_NOT_FOUND 0xB
#define RESPONSE_OK 0xC
#define RESPONSE_LED_OK 0xD
#define RESPONSE_VIBRATE_OK 0xE
#define RESPONSE_INFO_OK 0xF
#define RESPONSE_PING 0x10
#define RESPONSE_NEWCON_OK 0x11
#define RESPONSE_DISNEWCON_OK 0x12
#define RESPONSE_DISCONNECT_OK 0x13
#define RESPONSE_FORGETKEYS_OK 0x14
#define RESPONSE_PLAYERLED_OK 0x15
#define RESPONSE_VERSION_OK 0x16
#define RESPONSE_COMMANDNOTFOUND 0x17