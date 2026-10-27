#pragma once
//
//    FILE: ADS7124.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-12-02
// PURPOSE: Arduino library for I2C ADS7142 dual ADC sensor monitor
//     URL: https://github.com/RobTillaart/ADS7142
//
//  read datasheet for details


#include "Arduino.h"
#include "Wire.h"
#include "ADS7142_registers.h"


#define ADS7142_LIB_VERSION          (F("0.1.0"))


//  ERROR CODES
#define ADS7142_OK         0
#define ADS7142_ERROR      -100


//  OPERATION MODES
enum OPMODE
{
  MANUAL_CHANNEL0     = 0,
  MANUAL_AUTOSEQ      = 4,
  AUTOMONITOR_AUTOSEQ = 6,
  HIGH_PRECISION      = 7
};

//  INPUT CONFIGURATION
enum CONFIG
{
  TWO_CHANNEL_SINGLE_END   = 0,
  ONE_CHANNEL_SINGLE_END   = 1,
  ONE_CHANNEL_DIFFERENTIAL = 2
};


class ADS7142
{
public:
  //       deviceAddress = 0x18..0x1F
  explicit ADS7142(const uint8_t deviceAddress = 0x18, TwoWire *wire = &Wire);
  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();


  //  RESET & CALIBRATION page 44
  void     reset();
  void     triggerOffsetCalibration();


  //  OPERATION MODE page 45
  void     setManualChannel0();
  void     setManualAutoSequencing();
  void     setAutoMonitoringAutoSequencing();
  void     setHighPrecision();
  //  check datasheet for return values getOperationMode
  uint8_t  getOperationMode();
  bool     getI2CHighSpeedMode();


  //  INPUT CONFIGURATION  page 46
  void     setTwoChannelSingleEnded();
  void     setOneChannelSingleEnded();
  void     setOneChannelPseudoDifferential();
  //  check datasheet for return values
  uint8_t  getChannelConfig();


  //  AUTO SEQUENCE CHANNEL ENABLE page 47,48
  void     setAutoSequenceChannel(uint8_t channel, bool enable);
  bool     getAutoSequenceChannel(uint8_t channel);
  void     startSequence();
  void     stopSequence();
  //  check datasheet for return values
  uint8_t  getSequenceStatus();


  //  OSCILLATOR and TIMING CONTROL REGISTERS page 49
  //  see datasheet, clock depends on oscillator
  //  Oscillator  |  Clock
  //  -----------------------
  //  HIGH = 0    |  21..255
  //  LOW  = 1    |  18..255
  void     setOscillatorClock(uint8_t osc, uint8_t clk);
  uint8_t  getOscillator();
  uint8_t  getClockSelect();  //  18..255


  //  DATA BUFFER CONTROL REGISTER page 50,51
  //  values allowed = {0,1,4,6} ==>  enum
  void     setDataBufferMode(uint8_t mode);
  uint8_t  getDataBufferMode();
  //  values allowed = {0,1,2,3} ==>  enum
  void     setDataFormat(uint8_t format);
  uint8_t  getDataFormat();
  //  values = {0..16}
  uint8_t  getDataBufferCount();


  //  ACCUMULATOR CONTROL REGISTERS page 52,53
  void     setAccumulatorEnable(bool enable);
  bool     getAccumulatorEnable();
  uint16_t getAccumulatorChannel0();
  uint16_t getAccumulatorChannel1();
  uint8_t  getAccumulatorCount();


  //  DIGITAL WINDOW COMPARATOR (DWC) REGISTERS page 54..59
  void     setDWCEnable(bool enable);
  bool     getDWCEnable();
  void     setAlertChannel(uint8_t channel, bool enable);
  bool     getAlertChannel(uint8_t channel);
  //  page 54..57
  void     setDWCThresholdHigh(uint8_t channel, uint16_t th);
  uint16_t getDWCThresholdHigh(uint8_t channel);
  void     setDWCThresholdLow(uint8_t channel, uint16_t th);
  uint16_t getDWCThresholdLow(uint8_t channel);
  void     setDWXHysteresis(uint8_t channel, uint8_t hysteresis);
  uint8_t  getDWXHysteresis(uint8_t channel);
  //  page 58,59
  void     setMaxEventCount(uint8_t count);
  uint8_t  getMaxEventCount();
  uint8_t  getAlertTriggerChannel();
  void     clearAlertLow(uint8_t channel);
  uint8_t  getAlertLow();
  void     clearAlertHigh(uint8_t channel);
  uint8_t  getAlertHigh();


  //  ALERT and BUSY
  void     setAlertPin(uint8_t alertPin);  //  sets pin
  uint8_t  getAlert();                     //  read alert pin
  void     setBusyPin(uint8_t busyPin);    //  sets pin
  uint8_t  getBusy();                      //  read busy pin

  //  ERROR HANDLING
  int      lastError();



/////////////////////////////////////////////
//
//  LOW LEVEL REGISTER
//
  int      readRegister(uint8_t reg);
  int      writeRegister(uint8_t reg, uint8_t value);


private:
  uint8_t   _address  = 0x18;
  int       _error    = 0;

  uint8_t   _mode     = 0;
  uint8_t   _alertPin = 0;
  uint8_t   _busyPin  = 0;

  TwoWire*  _wire;
};


//  -- END OF FILE --


