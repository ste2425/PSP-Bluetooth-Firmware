#include "commandManager.h"

void processCommand(uint8_t command) {
    for (int i = 0; i < commandCount; ++i) {
        if (commands[i].code == command) {
            commands[i].function();
            return;
        }
    }

    SerialWrapper_write(RESPONSE_COMMANDNOTFOUND);
}