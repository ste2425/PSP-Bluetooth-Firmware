#include "commands.h"

// Command to get the current state of a controller at the specified index.
void firmwareVersionExecute(void) {
    // TODO Automate this
    const char* version = "[REPLACE]";
    uint8_t len = strlen(version);
    SerialWrapper_write(RESPONSE_VERSION_OK);
    SerialWrapper_write(len);
    SerialWrapper_write((const uint8_t*)version, len);
}