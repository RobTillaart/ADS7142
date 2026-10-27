
[![Arduino CI](https://github.com/RobTillaart/ADS7142/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ADS7142/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ADS7142/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ADS7142/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ADS7142/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ADS7142/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ADS7142.svg?maxAge=3600)](https://github.com/RobTillaart/ADS7142/releases)


# ADS7142

Arduino library for I2C ADS7142 2-Channel ADC Programmable Sensor Monitor



## Description

**Experimental**

At the moment it is **work in progress**.

This library is written based upon the datasheet of September 2017.

The ADS7142 autonomously monitors signals from devices and / or sensors.
I can provide a wake up event (typical interrupt) if the output of the 
monitored device changes (to certain extend).

The ADS7142 has two channels (ADC's) so two devices can be monitored.
The two channels can also be combined into one (differential ?)

The trigger con be configured by means of thresholds (HIGH / LOW) or an event Counter.
(Read datasheet for the details.)

Note: the ADS7142 operates at 1.65 - 3.6 Volts, so it cannot be used directly
by a 5 Volt MCU. Use a voltage or level convertor if needed.

Feedback as always is welcome.


### Compatibles

There are two types known, the ADS7142 and ADS7142-Q1.
The Q1 is automotive certified.


## Related

- https://nl.mouser.com/en/new/mikroe/mikroe-adc-16-click/
- https://nl.mouser.com/en/new/texas-instruments/ti-ads7142-sensor-monitors/

## Hardware

### Pins

|  Pin    |  Description  |
|:-------:|:--------------|
|  AVCC   |  analog supply and reference 
|  AIN0   |  positive (1 channel mode) or channel 0
|  AIN1   |  negative (1 channel mode) or channel 1
|  ADDR   |  address selection - see **datasheet table 2** default 0x18?
|  BUSY   |  HIGH when busy, LOW when READY
|  ALERT  |  Alert pin, active low, connect pull up to DVDD
|  SDA    |  I2C data
|  SCL    |  I2C clock
|  DVDD   |  digital IO supply 
|  GND    |  ground


Note the library can only poll the ALERT and BUSY pin.

Event driven part, e.g. wake up event is outside library scope.


## I2C

### I2C Address

- 8 addresses are supported 0x18..0x1F - see **datasheet table 2**

### I2C Performance

- speed up to 3.4 MHz (High speed I2C)

### I2C multiplexing

Sometimes you need to control more devices than possible with the default
address range the device provides.
This is possible with an I2C multiplexer e.g. TCA9548 which creates up
to eight channels (think of it as I2C subnets) which can use the complete
address range of the device.

Drawback of using a multiplexer is that it takes more administration in
your code e.g. which device is on which channel.
This will slow down the access, which must be taken into account when
deciding which devices are on which channel.
Also note that switching between channels will slow down other devices
too if they are behind the multiplexer.

- https://github.com/RobTillaart/TCA9548


## Interface

### Constructor

- **ADS7142(const uint8_t deviceAddress = 0x20, TwoWire \*wire = &Wire)** constructor
- **bool begin(int sda, int scl)**
- **bool begin()**
- **bool isConnected()**
- **uint8_t getAddress()**
- **void reset()**





## Future

#### Must

- improve documentation.
- buy hardware ADS7142.
- test with hardware.
- add examples.

#### Should 

- are there compatible IC's that this library can support?
  - identical or similar interface?
- unit test if possible


#### Could


#### Won't


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

