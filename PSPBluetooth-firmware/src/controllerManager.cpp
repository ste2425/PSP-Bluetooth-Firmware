#include "controllerManager.h"

ControllerPtr controllers[BP32_MAX_GAMEPADS];

// BP32 default to accepting new connections
// we need to disable that after a small deay to allow it to finish its config
TimerEvent setupDisableNewConsTimers;

// hoisting baby - Is it called hoisting when not writing JS?
void onConnectedController(ControllerPtr ctl);
void onDisconnectedController(ControllerPtr ctl);
void processControllers();
void resetController(uint8_t index);
void processControllers();
void processGamepad(uint8_t index, ControllerPtr ctl);
void onSetupDisableNewConsTimers();

void controllerManagerSetup(void) {
    BP32.setup(&onConnectedController, &onDisconnectedController);

    BP32.enableVirtualDevice(false);

    BP32.enableBLEService(false);

    setupDisableNewConsTimers.set(500, onSetupDisableNewConsTimers);
}

void controllerManagerForgetBluetoothKeys(void) {
    BP32.forgetBluetoothKeys();
}

void controllerManagerLoop(void) {
    BP32.update();
    setupDisableNewConsTimers.update();
}

void controllerManagerEnableNewConnections() {
    // Id be supprised if this is called before the timer runs but just incase lets stop the timer
    setupDisableNewConsTimers.disable();

    BP32.enableNewBluetoothConnections(true);
}

void controllerManagerDisableNewConnections(void) {
    BP32.enableNewBluetoothConnections(false);
}

ControllerPtr controlerManagerGetController(uint8_t index) {
    if (index >= BP32_MAX_GAMEPADS)
        return nullptr;

    auto controller = controllers[index];

    if (controller && controller->isConnected())
        return controller;

    return nullptr;
}

void onConnectedController(ControllerPtr ctl) {
    bool foundEmptySlot = false;
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (controllers[i] == nullptr) {
            controllers[i] = ctl;
            foundEmptySlot = true;
            break;
        }
    }
}

void onDisconnectedController(ControllerPtr ctl) {
    bool foundController = false;

    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (controllers[i] == ctl) {
            controllers[i] = nullptr;
            foundController = true;
            break;
        }
    }
}

void onSetupDisableNewConsTimers() {
    setupDisableNewConsTimers.disable();

    controllerManagerDisableNewConnections();
}