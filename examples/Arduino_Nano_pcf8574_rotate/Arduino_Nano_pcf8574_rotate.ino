#include <Arduino.h>
#include <Wire.h>
#include "PCF8574-I2C.h"

PCF8574_I2C::PCF8574 pcf{0x20, &Wire};
void setup() {
   Serial.begin(115200);
   Serial.println("\n\nPCF8574 Test file with Arduino-Nano\n");

   Wire.begin();

   if (pcf.begin() == PCF8574_I2C::PCF8574_STATE_OK) {
      Serial.print("\tPCF8574 Connection OK!\n");
   }
   else {
      Serial.print("\tNO PCF8574 device found!\n");
   }

   pcf.resetPort();
   // ### --- READ PORT --- ###

   // set Port to 1
   pcf.setPort(0b11111110);
   delay(5000);
}

void loop() {
   for (int i = 0; i < 140; ++i) {
      pcf.rotateLeft();
      delay(200);
   }
   for (int i = 0; i < 140; ++i) {
      pcf.rotateRight();
      delay(200);
   }
}