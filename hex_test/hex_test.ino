#include <IRremote.hpp>

const int IR_PIN = 2;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("Press remote buttons to read codes...");
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("Code: 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.resume();
  }
}
