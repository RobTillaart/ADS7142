
[![Arduino CI](https://github.com/RobTillaart/ADS7142/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ADS7142/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ADS7142/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ADS7142/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ADS7142/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/ADS7142.svg)](https://github.com/RobTillaart/ADS7142/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ADS7142/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ADS7142.svg?maxAge=3600)](https://github.com/RobTillaart/ADS7142/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/ADS7142.svg)](https://registry.platformio.org/libraries/robtillaart/ADS7142)


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

```
#include "ADS7142.h"
```

### Constructor

- **ADS7142(const uint8_t deviceAddress = 0x18, TwoWire \*wire = &Wire)** constructor
- **bool begin()**
- **bool isConnected()**
- **uint8_t getAddress()**

### Reset and calibration

Page 44.

- **void reset()**
- **void triggerOffsetCalibration()**

### Operation mode

Page 45.

- **void setManualChannel0()**
- **void setManualAutoSequencing()**
- **void setAutoMonitoringAutoSequencing()**
- **void setHighPrecision()**
- **uint8_t getOperationMode()**
- **bool getI2CHighSpeedMode()**

### Input configuration

Page 46

- **void setTwoChannelSingleEnded()**
- **void setOneChannelSingleEnded()**
- **void setOneChannelPseudoDifferential()**
- **uint8_t getChannelConfig()**
  
### Auto sequence channel enable

Page 47,48

- **void setAutoSequenceChannel(uint8_t channel, bool enable)**
- **bool getAutoSequenceChannel(uint8_t channel)**
- **void startSequence()**
- **void stopSequence()**
- **uint8_t getSequenceStatus()**

### Oscillator and timing

Page 49

- **void setOscillatorClock(uint8_t osc, uint8_t clk)**
- **uint8_t getOscillator()**
- **uint8_t getClockSelect()**  returns 18..255

### Data buffer control

Page 50,51

- **void setDataBufferMode(uint8_t mode)** mode = {0,1,4,6}
- **uint8_t  getDataBufferMode()**
- **void     setDataFormat(uint8_t format)** format = {0,1,2,3}
- **uint8_t  getDataFormat()**
- **uint8_t  getDataBufferCount()** returns 0..16

### Accumulator control

Page 52,53

- **void setAccumulatorEnable(bool enable)**
- **bool getAccumulatorEnable()**
- **uint16_t getAccumulatorChannel0()**
- **uint16_t getAccumulatorChannel1()**
- **uint8_t getAccumulatorCount()**

### Digital Window Comparator (DWC)

Page 54..59

- **void setDWCEnable(bool enable)**
- **bool getDWCEnable()**
- **void setAlertChannel(uint8_t channel, bool enable)**
- **bool getAlertChannel(uint8_t channel)**

Page 54..57
- **void setDWCThresholdHigh(uint8_t channel, uint16_t th)**
- **uint16_t getDWCThresholdHigh(uint8_t channel)**
- **void setDWCThresholdLow(uint8_t channel, uint16_t th)**
- **uint16_t getDWCThresholdLow(uint8_t channel)**
- **void setDWXHysteresis(uint8_t channel, uint8_t hysteresis)**
- **uint8_t getDWXHysteresis(uint8_t channel)**

Page 58,59
- **void setMaxEventCount(uint8_t count)**
- **uint8_t getMaxEventCount()**
- **uint8_t getAlertTriggerChannel()**
- **void clearAlertLow(uint8_t channel)**
- **uint8_t getAlertLow()**
- **void clearAlertHigh(uint8_t channel)**
- **uint8_t getAlertHigh()**


### ALERT and BUSY

Pins for polling the ADS7142 **ALERT** and **BUSY** pins.
If not set these pins cannot be read.

- **uint8_t setAlert(uint8_t alertPin)**
- **uint8_t getAlert()**
- **uint8_t setBusy(uint8_t busyPin)**
- **uint8_t getBusy()**

## Error

- **int getLastError()**
  
|  Value  |  Description        |  Notes  |
|:-------:|:--------------------|:--------|
|  0      |  ADS7142_OK         |
|  -100   |  ADS7142_ERROR      | generic indicator


## Future

#### Must

- improve documentation. (a lot).
- elaborate API
- add datasheet to repo
- buy and test with hardware ADS7142.

#### Should 

- add examples.
- improve error handling

#### Could

- unit test if possible
- are there compatible IC's that this library can support?
  - identical or similar interface?


#### Won't


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

