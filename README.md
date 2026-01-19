# PCF8574-I2C Library
[![Spell Check](https://github.com/hasenradball/PCF8574-I2C/actions/workflows/spell_checker.yml/badge.svg)](https://github.com/hasenradball/PCF8574-I2C/actions/workflows/spell_checker.yml)
[![Compile Examples](https://github.com/hasenradball/PCF8574-I2C/actions/workflows/compile_examples.yml/badge.svg)](https://github.com/hasenradball/PCF8574-I2C/actions/workflows/compile_examples.yml)
[![Generate Doxygen Documentation](https://github.com/hasenradball/PCF8574-I2C/actions/workflows/doxygen.yml/badge.svg)](https://github.com/hasenradball/PCF8574-I2C/actions/workflows/doxygen.yml)

Arduino Library for PCF8574, a 8-port GPIO exander via i2c

![PCF8574_dil.jpg](docs/PCF8574_dil.jpg)

## Contents
* [Library Documentation](#library-documentation)
* [Library Usage](#library-usage)
* [License](#license)
* [Helpful Links](#helpful-links)

## Library Documentation
The library documentation is mainly placed in the following pdf document:<br>[PCF8574-I2C-Documentation.pdf](https://github.com/hasenradball/PCF8574-I2C/blob/gh-pages/PCF8574-I2C-Documentation.pdf)<br> or located under the following github pages [github.io](https://hasenradball.github.io/PCF8574-I2C).<br>
Additionally in combination with the technical datasheet of microchip [PCF8574-Datasheet](./docs/PCF8574-Datasheet.pdf).


## Library Usage
### Controllers
The library is intended to be used on each microcontroller for Example:<br>
* Arnuino Nano
* Arduino Nano 33 IOT
* ESP8266
* ESP32
* etc ...

### Usage the PCF8574-I2C Library in the Code
Include the library in you project via:

`#include <PCF8574-I2C.h>`

Instance an new PCF8574 object by:

`PCF8574_I2C::PCF8574 pcf{0x20, &Wire};`<br>
or simply use implicit defined Wire object like:<br>
`PCF8574_I2C::PCF8574 pcf{0x20};`<br>

Now you can use the object and his members as normal like:

```
PCF8574_I2C::PCF8574 pcf{0x20, &Wire};
void setup() {
   Serial.begin(115200);
   Serial.print("\n\nPCF8574 Test file with ESP8266-01\n");

   Wire.begin(2, 0);

   if (pcf.begin() == PCF8574_I2C::PCF8574_STATE_OK) {
      Serial.print("\tPCF8574 Connection OK!\n");
   }
   else {
      Serial.print("\tNO PCF8574 device found!\n");
   }
   pcf.resetPort();
}
```


Please refer to the examples and the above mentioned documentation files.

### Status Codes of PCF8574
The following status codes exists:

* PCF8574_STATE_OK     {0};
* PCF8574_ERROR_PIN    {-1};
* PCF8574_ERROR_I2C    {-2};
* PCF8574_ERROR_VALUE  {-3};

# License
This library is licensed under MIT Licence.

[PCF8574-I2C License](https://github.com/hasenradball/PCF8574-I2C/blob/master/LICENSE)


# Helpful Links
* [ESP8266-01-Adapter](https://esp8266-01-adapter.de)

