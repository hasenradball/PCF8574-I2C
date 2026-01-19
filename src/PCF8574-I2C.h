/**
 * @file PCF8574-I2C.h
 * @author Frank Häfele (mail@frankhaefele.de)
 * @brief Library for a PCF8574 GPIO expander
 * @version 1.1.0
 * @date 2026-01-12
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#pragma once 

#define __PCF8574_I2C_H__

#include "Wire.h"

namespace PCF8574_I2C {

    constexpr const char *PCF8574_LIB_VERSION   {"1.1.0"};

   /**
   * @brief constant which states all ok, no error
   * 
   */
   constexpr int8_t PCF8574_STATE_OK           {0x00};
  
  /**
   * @brief constant which states a wrong pin number was used
   * 
   */
   constexpr int8_t PCF8574_ERROR_PIN          {-1};

  /**
   * @brief constant which states an error during I2C communication
   * 
   */
   constexpr int8_t PCF8574_ERROR_I2C          {-2};

  /**
   * @brief constant which states that there was an error regarding a parameter value
   * 
   */
   constexpr int8_t PCF8574_ERROR_VALUE        {-3};


   class PCF8574 {
      public:
         /**
          * @brief Construct a new PCF8574 object
          * 
          * @param address of PCF8574 device 
          * @param wire pointer of TwoWire object
          */
         PCF8574(const uint8_t address = 0x20, TwoWire* wire = &Wire);
         
         /**
          * @brief begin method which initializes and verifies connection.
          * Calls isDevicePresent()
          * 
          * @retval  0: if device is connected
          * @retval -2: if connection failed due to missing connection or line error.
          */
         int8_t begin() const;

         /**
          * @brief reset the PCF8574 device, set all port pins to input
          * 
          * @return int8_t status of the write command
          * 
          * @retval  0: successfull
          * @retval -2: error on i2c connection
          */
         int8_t resetPort();

         /**
          * @brief read pin(s) from port
          * 
          * @param pin give pin number 0...7; or ommit for all read all port pins
          * @return int8_t return error code or value
          * 
          * @retval >0: read was ok => return pin/Port value
          * @retval <0: error during readPin => return error code
          */
         int16_t readPin(int8_t pin = -1);
         
         /**
          * @brief Set the a specific pin on the PCF8474 to 0 or 1
          * 
          * @param pin number of port pin P0...P7
          * @param value value of pin 0 or 1
          * @return int8_t status of the write command
          * 
          * @retval  0: successfull
          * @retval -1: pin error; wrong pin number
          * @retval -2: error on i2c connection
          * @retval -3: wrong value for pin
          */
         int8_t setPin(uint8_t pin, uint8_t value);

         /**
          * @brief Set the Port at once to an value 
          * 
          * @param value for port to set
          * @return int8_t status of the write command
          * 
          * @retval  0: successfull
          * @retval -2: error on i2c connection
          */
         int8_t setPort(uint8_t value);

         /**
          * @brief toggle pins by give a mask which pin to toggle
          * 
          * @param mask define which pin to toggle like: 0b10010101
          * @return int8_t status of the write command
          * 
          * @retval  0: successfull
          * @retval -2: error on i2c connection
          */
         int8_t toggle(uint8_t mask);

         /**
          * @brief rotate Port to the left
          * 
          * @return int8_t status of the write command
          * 
          * @retval  0: successfull
          * @retval -2: error on i2c connection
          */
         int8_t rotateLeft();

         /**
          * @brief rotate port to the right
          * 
          * @return int8_t status of the write command
          * 
          * @retval  0: successfull
          * @retval -2: error on i2c connection
          */
         int8_t rotateRight();


      private:
         // internal address of PCF8574 device
         uint8_t _address;

         // internal pointer to wire object
         TwoWire* _wire;

         // holds the last error
         int8_t _error;

         // holds the las readings from device
         uint8_t _input{0};

         // holds the last sending to device
         uint8_t _output{0xFF};


         /**
          * @brief checks communication to device
          * 
          * @return bool status of communication or connection
          * 
          * @retval true: connection OK
          * @retval false: not connected, wiring failure or wrong address
          */
         bool isDevicePresent() const;

         /**
          * @brief read port from PCF8574 device
          * 
          * @return int8_t status of read command
          *
          * @retval 0: successfull
          * @retval -2: error in i2C read request
          */
         int8_t readPort();

         /**
          * @brief write value to PCF8574 Port
          * 
          * @param value data to write
          * @return int8_t status of I2C write
          * 
          * @retval  0: write sucessfull
          * @retval -2: error on write
          */
         int8_t writePort(uint8_t value);

         /**
          * @brief check if value for port pin is not greater than 7
          * 
          * @param pin of port P0...P7
          * @return true pin is not greather than 7
          * @return false pin is greather than 7
          */
         bool isPinValid(int8_t pin);


   };

 }