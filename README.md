
[![Arduino CI](https://github.com/RobTillaart/TSL235R/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TSL235R/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TSL235R.svg?maxAge=3600)](https://github.com/RobTillaart/TSL235R/releases)


# TSL235R

Arduino library for the TSL235R light to frequency convertor


## Description

This library does not measure the frequency but has some functionsto compensate e.g. 
for wavelength.

The library is not tested extensively yet.


## Connector

```
// PIN 1 - GND
// PIN 2 - VDD      2.7 V .. 5.5 V
// PIN 3 - SIGNAL   1 Hz  .. 800 KHz
```


## Interface

- **TSL235R(float voltage = 5.0)** constructor
- **float irradiance(uint32_t hz)**

- **void setWavelength(uint16_t wavelength)** sets the wavelength so the formulas can use a correction factor.
- **uint16_t getWavelength()** returns the set wavelength
- **float getWaveLengthFactor()** returns the correction factor

  // voltage gives a small compensation ( < 1.5% )
- **void setVoltage(float voltage)** sets the voltage so the formulas can use a correction factor.
- **float getVoltage()**


## Operations

See examples for typical usage.
