#include <Bluepad32.h>

#include "src/commandManager.h"
#include "src/controllerManager.h"
#include "src/Serial.h"

#define SERIAL_BAUD 115200
#define SERIAL_RX_PIN 16
#define SERIAL_TX_PIN 18

void setup() {
    SerialWrapper_begin(SERIAL_BAUD, SERIAL_8N1, SERIAL_RX_PIN, SERIAL_TX_PIN);

    controllerManagerSetup();
}

void loop() {
    controllerManagerLoop();
    
    if (SerialWrapper_available()) {
      char command = SerialWrapper_read();

      processCommand(command);
    }

    delay(1);
}
