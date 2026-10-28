//
//    FILE: ADS7142.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-12-02
// PURPOSE: Arduino library for I2C ADS7142 dual ADC Sensor Monitor
//     URL: https://github.com/RobTillaart/ADS7142


#include "ADS7142.h"


ADS7142::ADS7142(const uint8_t deviceAddress, TwoWire *wire)
{
  _address  = deviceAddress;
  _wire     = wire;
  _error    = ADS7142_OK;
  _alertPin = 255;
  _busyPin  = 255;
}

bool ADS7142::begin()
{
  if (! isConnected()) return false;
  return true;
}

bool ADS7142::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}

uint8_t ADS7142::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  RESET & CALIBRATION page 44
//
void ADS7142::reset()
{
  writeRegister(ADS7142_WKEY, 0x0A);
  writeRegister(ADS7142_DEVICE_RESET, 0x01);
  //  TODO reset state...
  _error    = ADS7142_OK;
}

void ADS7142::triggerOffsetCalibration()
{
  writeRegister(ADS7142_OFFSET_CAL, 0x01);
}


/////////////////////////////////////////////
//
//  READ Page 24
//
uint16_t ADS7142::read()
{
  return readData2();
}

uint8_t ADS7142::read(uint16_t data[], uint8_t size)
{
  if (size == 0) return 0;
  uint8_t n = getDataBufferCount();
  if (size < n) n = size;
  //  TODO test
  //  fetch data per measurement if possible
  //  optimize later
  for (uint8_t i = 0; i < n; i++)
  {
    data[i] = readData2();
  }
  return n;
}

/////////////////////////////////////////////
//
//  OPERATION MODE page 45
//
void ADS7142::setManualChannel0()
{
  writeRegister(ADS7142_OPMODE_SEL, MANUAL_CHANNEL0);
}

void ADS7142::setManualAutoSequencing()
{
  writeRegister(ADS7142_OPMODE_SEL, MANUAL_AUTOSEQ);
}

void ADS7142::setAutoMonitoringAutoSequencing()
{
  writeRegister(ADS7142_OPMODE_SEL, AUTOMONITOR_AUTOSEQ);
}

void ADS7142::setHighPrecision()
{
  writeRegister(ADS7142_OPMODE_SEL, HIGH_PRECISION);
}

uint8_t ADS7142::getOperationMode()
{
  return readRegister(ADS7142_OPMODE_SEL);
}

bool ADS7142::getI2CHighSpeedMode()
{
  return readRegister(ADS7142_OPMODE_I2CMODE_STATUS) >> 2;
}


/////////////////////////////////////////////
//
//  INPUT CONFIGURATION page 46
//
void ADS7142::setTwoChannelSingleEnded()
{
  writeRegister(ADS7142_CHANNEL_INPUT_CFG, TWO_CHANNEL_SINGLE_END);
  // same as 0x03
}

void ADS7142::setOneChannelSingleEnded()
{
  writeRegister(ADS7142_CHANNEL_INPUT_CFG, ONE_CHANNEL_SINGLE_END);
}

void ADS7142::setOneChannelPseudoDifferential()
{
  writeRegister(ADS7142_CHANNEL_INPUT_CFG, ONE_CHANNEL_DIFFERENTIAL);
}

uint8_t ADS7142::getChannelConfig()
{
  return readRegister(ADS7142_CHANNEL_INPUT_CFG);
}


/////////////////////////////////////////////
//
//  AUTO SEQUENCE CHANNEL ENABLE page 47
//
void ADS7142::setAutoSequenceChannel(uint8_t channel, bool enable)
{
  if (channel > 1)
  {
    //  _error =
    return;
  }
  uint8_t mask = readRegister(ADS7142_AUTO_SEQ_CHEN);
  if (channel == 0)
  {
    if (enable) mask |= 0x01;
    else        mask &= 0xFE;
  }
  else
  {
    if (enable) mask |= 0x02;
    else        mask &= 0xFD;
  }
  writeRegister(ADS7142_AUTO_SEQ_CHEN, mask);
}

bool ADS7142::getAutoSequenceChannel(uint8_t channel)
{
  if (channel > 1)
  {
    // _error =
    return false;
  }
  uint8_t mask = readRegister(ADS7142_AUTO_SEQ_CHEN);
  if (channel == 0) return (mask & 0x01) > 0;
  return (mask & 0x02) > 0;
}

void ADS7142::startSequence()
{
  writeRegister(ADS7142_START_SEQUENCE, 1);
}

void ADS7142::stopSequence()
{
  writeRegister(ADS7142_ABORT_SEQUENCE, 1);
}

uint8_t ADS7142::getSequenceStatus()
{
  return readRegister(ADS7142_SEQUENCE_STATUS);
}


/////////////////////////////////////////////
//
//  OSCILLATOR and TIMING CONTROL REGISTERS page 49
//
void ADS7142::setOscillatorClock(uint8_t osc, uint8_t clock)
{
  if (osc > 1)
  {
    //  _error =
    return;
  }
  writeRegister(ADS7142_OSC_SEL, osc);
  uint8_t data = clock;
  if ((osc == 0) && (data < 21)) data = 21;   //  OSC == HIGH
  if ((osc == 1) && (data < 18)) data = 18;   //  OSC == LOW
  writeRegister(ADS7142_nCLK_SEL, data);
}

uint8_t ADS7142::getOscillator()
{
  return readRegister(ADS7142_OSC_SEL);
}

uint8_t ADS7142::getClockSelect()
{
  return readRegister(ADS7142_nCLK_SEL);
}


/////////////////////////////////////////////
//
//  DATA BUFFER CONTROL REGISTER page 50
//
void ADS7142::setDataBufferMode(uint8_t mode)
{
  if (mode == 0 ||  mode == 1 || mode == 4 || mode == 6)
  {
    writeRegister(ADS7142_DATA_BUFFER_OPMODE, mode);
  }
}

uint8_t ADS7142::getDataBufferMode()
{
  return readRegister(ADS7142_DATA_BUFFER_OPMODE);
}

void ADS7142::setDataFormat(uint8_t format)
{
  if (format > 3) return;
  writeRegister(ADS7142_DOUT_FORMAT_CFG, format);
}

uint8_t ADS7142::getDataFormat()
{
  return readRegister(ADS7142_DOUT_FORMAT_CFG);
}

uint8_t ADS7142::getDataBufferCount()
{
  return readRegister(ADS7142_DATA_BUFFER_STATUS);
}


/////////////////////////////////////////////
//
//  ACCUMULATOR CONTROL REGISTERS page 52, 53
//
void ADS7142::setAccumulatorEnable(bool enable)
{
  uint8_t mask = 0x00;
  if (enable) mask = 0x0F;
  writeRegister(ADS7142_ACC_EN, mask);
}

bool ADS7142::getAccumulatorEnable()
{
  return readRegister(ADS7142_ACC_EN) > 0;
}

uint16_t ADS7142::getAccumulatorChannel0()
{
  uint16_t data = readRegister(ADS7142_ACC_CH0_MSB);
  data |= readRegister(ADS7142_ACC_CH0_LSB);
  return data;
}

uint16_t ADS7142::getAccumulatorChannel1()
{
  uint16_t data = readRegister(ADS7142_ACC_CH1_MSB);
  data |= readRegister(ADS7142_ACC_CH1_LSB);
  return data;
}

uint8_t ADS7142::getAccumulatorCount()
{
  return readRegister(ADS7142_ACCUMULATOR_STATUS);
}


/////////////////////////////////////////////
//
//  DIGITAL WINDOW COMPARATOR REGISTERS page 54..59
//
void ADS7142::setDWCEnable(bool enable)
{
  uint8_t mask = 0x00;
  if (enable) mask = 0x01;
  writeRegister(ADS7142_ALERT_DWC_EN, mask);
}

bool ADS7142::getDWCEnable()
{
  return readRegister(ADS7142_ALERT_DWC_EN) > 0;
}

void ADS7142::setAlertChannel(uint8_t channel, bool enable)
{
  if (channel > 1)
  {
    //  _error =
    return;
  }
  uint8_t mask = readRegister(ADS7142_ALERT_CHEN);
  if (channel == 0)
  {
    if (enable) mask |= 0x01;
    else        mask &= 0xFE;
  }
  else
  {
    if (enable) mask |= 0x02;
    else        mask &= 0xFD;
  }
  writeRegister(ADS7142_ALERT_CHEN, mask);
}

bool ADS7142::getAlertChannel(uint8_t channel)
{
  if (channel > 1)
  {
    // _error =
    return false;
  }
  uint8_t mask = readRegister(ADS7142_ALERT_CHEN);
  if (channel == 0) return (mask & 0x01) > 0;
  return (mask & 0x02) > 0;
}

void ADS7142::setDWCThresholdHigh(uint8_t channel, uint16_t th)
{
  if (channel > 1)
  {
    //  _error =
    return;
  }
  if (th > 0x0FFF)
  {
    //  _error =
    return;
  }
  uint8_t regLSB = ADS7142_DWC_HTH_CH0_LSB;
  uint8_t regMSB = ADS7142_DWC_HTH_CH0_MSB;
  if (channel == 1)
  {
    regLSB = ADS7142_DWC_HTH_CH1_LSB;
    regMSB = ADS7142_DWC_HTH_CH1_MSB;
  }
  writeRegister(regLSB, th & 0xFF);
  writeRegister(regMSB, (th >> 8) & 0x0F);
}

uint16_t ADS7142::getDWCThresholdHigh(uint8_t channel)
{
  if (channel > 1)
  {
    //  _error =
    return 0;
  }
  uint8_t regLSB = ADS7142_DWC_HTH_CH0_LSB;
  uint8_t regMSB = ADS7142_DWC_HTH_CH0_MSB;
  if (channel == 1)
  {
    regLSB = ADS7142_DWC_HTH_CH1_LSB;
    regMSB = ADS7142_DWC_HTH_CH1_MSB;
  }
  uint16_t value = readRegister(regMSB);
  value <<= 8;
  value += readRegister(regLSB);
  return value;
}

void ADS7142::setDWCThresholdLow(uint8_t channel, uint16_t th)
{
  if (channel > 1)
  {
    //  _error =
    return;
  }
  if (th > 0x0FFF)
  {
    //  _error =
    return;
  }
  uint8_t regLSB = ADS7142_DWC_LTH_CH0_LSB;
  uint8_t regMSB = ADS7142_DWC_LTH_CH0_MSB;
  if (channel == 1)
  {
    regLSB = ADS7142_DWC_LTH_CH1_LSB;
    regMSB = ADS7142_DWC_LTH_CH1_MSB;
  }
  writeRegister(regLSB, th & 0xFF);
  writeRegister(regMSB, (th >> 8) & 0x0F);
}

uint16_t ADS7142::getDWCThresholdLow(uint8_t channel)
{
  if (channel > 1)
  {
    //  _error =
    return 0;
  }
  uint8_t regLSB = ADS7142_DWC_LTH_CH0_LSB;
  uint8_t regMSB = ADS7142_DWC_LTH_CH0_MSB;
  if (channel == 1)
  {
    regLSB = ADS7142_DWC_LTH_CH1_LSB;
    regMSB = ADS7142_DWC_LTH_CH1_MSB;
  }
  uint16_t value = readRegister(regMSB);
  value <<= 8;
  value += readRegister(regLSB);
  return value;
}

void ADS7142::setDWXHysteresis(uint8_t channel, uint8_t hysteresis)
{
  if (channel > 1)
  {
    //  _error =
    return;
  }
  if (hysteresis > 0x3F)
  {
    //  _error =
    return;
  }
  uint8_t regHys = ADS7142_DWC_HYS_CH0;
  if (channel == 1)
  {
    regHys = ADS7142_DWC_HYS_CH1;
  }
  writeRegister(regHys, hysteresis);
}

uint8_t ADS7142::getDWXHysteresis(uint8_t channel)
{
  if (channel > 1)
  {
    //  _error =
    return 0;
  }
  uint8_t regHys = ADS7142_DWC_HYS_CH0;
  if (channel == 1)
  {
    regHys = ADS7142_DWC_HYS_CH1;
  }
  return readRegister(regHys);
}


/*
ADS7142_ALERT_LOW_FLAGS             RW
ADS7142_ALERT_HIGH_FLAGS            RW
*/
void ADS7142::setMaxEventCount(uint8_t count)
{
  if (count > 15)
  {
    //  _error =
    return;
  }
  writeRegister(ADS7142_PRE_ALT_MAX_EVENT_COUNT, count << 4);
}

uint8_t ADS7142::getMaxEventCount()
{
  return readRegister(ADS7142_PRE_ALT_MAX_EVENT_COUNT) >> 4;
}

uint8_t ADS7142::getAlertTriggerChannel()
{
  return (readRegister(ADS7142_ALERT_TRIG_CHID) >> 4) & 0x01;
}

void ADS7142::clearAlertLow(uint8_t channel)
{
  uint8_t mask = 0xFF;  //  clear all
  if (channel == 0) mask = 0x01;
  if (channel == 1) mask = 0x02;
  writeRegister(ADS7142_ALERT_LOW_FLAGS, mask);
}

uint8_t ADS7142::getAlertLow()
{
  return readRegister(ADS7142_ALERT_LOW_FLAGS) & 0x03;
}

void ADS7142::clearAlertHigh(uint8_t channel)
{
  uint8_t mask = 0xFF;  //  clear all
  if (channel == 0) mask = 0x01;
  if (channel == 1) mask = 0x02;
  writeRegister(ADS7142_ALERT_HIGH_FLAGS, mask);
}

uint8_t ADS7142::getAlertHigh()
{
  return readRegister(ADS7142_ALERT_HIGH_FLAGS) & 0x03;
}


/////////////////////////////////////////////
//
//  ALERT and BUSY
//
void ADS7142::setAlertPin(uint8_t alertPin)
{
  _alertPin = alertPin;
  pinMode(_alertPin, INPUT_PULLUP);
}

bool ADS7142::hasAlert()
{
  if (_alertPin == 255) return false;
  return digitalRead(_alertPin) == LOW;
}

void ADS7142::setBusyPin(uint8_t busyPin)
{
  _busyPin = busyPin;
  pinMode(_busyPin, INPUT_PULLUP);
}

bool ADS7142::isBusy()
{
  if (_busyPin == 255) return false;
  return digitalRead(_busyPin) == LOW;
}


/////////////////////////////////////////////
//
//  ERROR HANDLING
//
int ADS7142::getLastError()
{
  int e = _error;
  _error = ADS7142_OK;
  return e;
}


/////////////////////////////////////////////
//
//  LOW LEVEL REGISTER
//
int ADS7142::readRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->endTransmission();   //  TODO handle error

  if (_wire->requestFrom(_address, (uint8_t)1) == 1)
  {
    return _wire->read();
  }
  //  TODO handle error
  return ADS7142_ERROR;
}


int ADS7142::writeRegister(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();
  return _error;
}


uint16_t ADS7142::readData2()
{
  if (_wire->requestFrom(_address, (uint8_t)2) == 2)
  {
    uint16_t data = _wire->read() << 8;
    data |= _wire->read();
    return data;
  }
  //  TODO handle error
  return -100;
}


//  -- END OF FILE --



