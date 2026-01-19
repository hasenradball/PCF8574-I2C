/**
 * @file PCF8574-I2C.cpp
 * @author Frank Häfele (mail@frankhaefele.de)
 * @brief Library for a PCF8574 GPIO expander
 * @version 1.1.0
 * @date 2026-01-12
 * 
 * @copyright Copyright (c) 2026
 * 
 */

 #include "PCF8574-I2C.h"

using namespace PCF8574_I2C;

PCF8574::PCF8574(uint8_t address, TwoWire* wire)
: _address{address}, _wire{wire}
{}

int8_t PCF8574::begin() const {
   if(!isDevicePresent()) {
      return PCF8574_ERROR_I2C;
   }
   return PCF8574_STATE_OK;
}

int8_t PCF8574::resetPort() {
   return setPort(0xFF);
}

int16_t PCF8574::readPin(int8_t pin) {
   if (!isPinValid(pin)) {
      _error = PCF8574_ERROR_PIN;
      return _error;
   }
   int8_t status = readPort();
   if (status == PCF8574_ERROR_I2C) {
      return _error;
   }
   return (pin < 0) ? static_cast<int16_t>(_input) : ((_input >> pin) & 1);
}

int8_t PCF8574::setPin(uint8_t pin, uint8_t value) {
   if (!isPinValid(pin)) {
      _error = PCF8574_ERROR_PIN;
      return _error;
   }
   if (value > 1) {
      _error = PCF8574_ERROR_VALUE;
      return _error;
   }
   uint8_t temp_out{_output};
   if (value) {
      temp_out |= (1 << pin);
   }
   else {
      temp_out &= ~(1 << pin);
   }
   return writePort(temp_out);
}

int8_t PCF8574::setPort(uint8_t value) {
   return writePort(value);
}

int8_t PCF8574::toggle(uint8_t mask) {
   uint8_t temp_out{_output};
   temp_out ^= mask;
   return writePort(temp_out);
}

int8_t PCF8574::rotateLeft() {
   uint8_t temp_out{(_output << 1U) | (_output >> 7U)};
   return writePort(temp_out);
}

int8_t PCF8574::rotateRight() {
   uint8_t temp_out{(_output >> 1U) | (_output << 7U)};
   return writePort(temp_out);
}

bool PCF8574::isDevicePresent() const {
   _wire->beginTransmission(_address);
   return _wire->endTransmission() == 0;
}

int8_t PCF8574::readPort() {
   if (_wire->requestFrom(_address, static_cast<uint8_t>(1)) != 1U) {
      _error = PCF8574_ERROR_I2C;
      return _error;
   }
   _input = _wire->read();
   _error = 0;
   return _error;
}

int8_t PCF8574::writePort(uint8_t value) {
   _wire->beginTransmission(_address);
   if (_wire->write(value)) {
      if (_wire->endTransmission() == 0) {
         _output = value;
         _error = 0;
         return PCF8574_STATE_OK;
      }
      else {
         _error = PCF8574_ERROR_I2C;
         return _error;
      }
   }
   else {
      _error = PCF8574_ERROR_I2C;
      return _error;
   }
}

bool PCF8574::isPinValid(int8_t pin) {
   return pin <= 7;
}