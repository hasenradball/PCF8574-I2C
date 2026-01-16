#include <Arduino.h>
#include <Wire.h>
#include "PCF8574-I2C.hpp"

PCF8574_I2C::PCF8574 pcf{0x20, &Wire};
void setup() {
   Serial.begin(115200);
   Serial.println("\n\nPCF8574 Test file with ESP8266-01\n");

   Wire.begin(2, 0);

   if (pcf.begin() == PCF8574_I2C::PCF8574_STATE_OK) {
      Serial.print("\tPCF8574 Connection OK!\n");
   }
   else {
      Serial.print("\tNO PCF8574 device found!\n");
   }

   pcf.resetPort();
   // ### --- READ PORT --- ###

   // read Pin 5
   auto ret = pcf.readPin(5);
   if (ret < 0) {
      Serial.print(F("Error on reading PIN\n"));
      Serial.printf("Error code: %d\n", ret);
   }
   else{
      Serial.printf("Pin P5 value: %d\n", ret);
   }

   delay(5000);

   // read Pin 7
   ret = pcf.readPin(7);
   if (ret < 0) {
      Serial.print(F("Error on reading PIN\n"));
      Serial.printf("Error code: %d\n", ret);
   }
   else {
      Serial.printf("Pin P7 value: %d\n", ret);
   }

   delay(5000);

   // read all Pins
   ret = pcf.readPin();
   if (ret < 0) {
      Serial.print(F("Error on reading PINS\n"));
      Serial.printf("Error code: %d\n", ret);
   }
   else {
      Serial.printf("Port value:   %d\n", ret);
   }

   delay(5000);

   // ### --- WRITE PORT --- ###

   // set pin 0 => 0
   Serial.printf("\n\nSet Pin 0 to 0: %d\n",(pcf.setPin(0, 0) == PCF8574_I2C::PCF8574_STATE_OK) ? 1 : 0 );

   delay(5000);

   // toggle via mask => pin1
   Serial.print(F("\nToggle Pin1\n"));
   pcf.toggle(0b00000010);
   delay(1000);
   pcf.toggle(0b00000010);
}

void loop() {
   // toggle
   Serial.print(F("Toggle Pin0 and Pin1\n"));
   pcf.toggle(0b00000011);
   delay(1000);
   Serial.print(F("Toggle Pin1 and Pin2\n"));
   pcf.toggle(0b00000110);
   delay(1000);
}