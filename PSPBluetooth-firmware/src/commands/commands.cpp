#include "commands.h"

const Command commands[] =
{
    {0x02, pingExecute},
    {0x03, controllerDataExecute},
    {0x04, enableNewConnectionsExecute},
    {0x05, disableNewConnectionsExecute},
    {0x06, disconnectControllerExecute},
    {0x07, controllerLEDExecute},
    {0x08, controllerVibrateExecute},
    {0x09, controllerInfoExecute},
    {0xA, forgetBluetoothKeysExecute},
    {0xB, controllerPlayerLEDExecute},
    {0xC, firmwareVersionExecute}
};

const size_t commandCount =
    sizeof(commands) / sizeof(commands[0]);