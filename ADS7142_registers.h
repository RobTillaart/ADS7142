#pragma once
//
//    FILE: ADS7124_registers.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-12-02
// PURPOSE: Arduino library for I2C ADS7142 dual ADC Sensor Monitor
//     URL: https://github.com/RobTillaart/ADS7124


//////////////////////////////////////
//
//  REGISTERS Table 5. Register Map  page 43
//
//  RESET REGISTERS page 44
const uint8_t ADS7142_WKEY                    = 0x17;
const uint8_t ADS7142_DEVICE_RESET            = 0x14;

//  FUNCTIONAL MODE SELECT REGISTERS page 45,46
const uint8_t ADS7142_OFFSET_CAL              = 0x15;
const uint8_t ADS7142_OPMODE_SEL              = 0x1C;
const uint8_t ADS7142_OPMODE_I2CMODE_STATUS   = 0x00;

//  INPUT CONFIG REGISTER page 46
const uint8_t ADS7142_CHANNEL_INPUT_CFG       = 0x24;

//  ANALOG MUX and SEQUENCER REGISTERS page 47,48
const uint8_t ADS7142_AUTO_SEQ_CHEN           = 0x20;
const uint8_t ADS7142_START_SEQUENCE          = 0x1E;
const uint8_t ADS7142_ABORT_SEQUENCE          = 0x1F;
const uint8_t ADS7142_SEQUENCE_STATUS         = 0x04;

//  OSCILLATOR and TIMING CONTROL REGISTERS page 49
const uint8_t ADS7142_OSC_SEL                 = 0x18;
const uint8_t ADS7142_nCLK_SEL                = 0x19;

//  DATA BUFFER CONTROL REGISTER page 50
const uint8_t ADS7142_DATA_BUFFER_OPMODE      = 0x2C;
const uint8_t ADS7142_DOUT_FORMAT_CFG         = 0x28;
const uint8_t ADS7142_DATA_BUFFER_STATUS      = 0x01;

//  ACCUMULATOR CONTROL REGISTERS page 52,53
const uint8_t ADS7142_ACC_EN                  = 0x30;
const uint8_t ADS7142_ACC_CH0_LSB             = 0x08;
const uint8_t ADS7142_ACC_CH0_MSB             = 0x09;
const uint8_t ADS7142_ACC_CH1_LSB             = 0x0A;
const uint8_t ADS7142_ACC_CH1_MSB             = 0x0B;
const uint8_t ADS7142_ACCUMULATOR_STATUS      = 0x02;

//  DIGITAL WINDOW COMPARATOR REGISTERS page 54..59
const uint8_t ADS7142_ALERT_DWC_EN            = 0x37;
const uint8_t ADS7142_ALERT_CHEN              = 0x34;
//  page 54,55,56
const uint8_t ADS7142_DWC_HTH_CH0_MSB         = 0x39;
const uint8_t ADS7142_DWC_HTH_CH0_LSB         = 0x38;
const uint8_t ADS7142_DWC_LTH_CH0_MSB         = 0x3B;
const uint8_t ADS7142_DWC_LTH_CH0_LSB         = 0x3A;
const uint8_t ADS7142_DWC_HYS_CH0             = 0x40;
//  page 56,57
const uint8_t ADS7142_DWC_HTH_CH1_MSB         = 0x3D;
const uint8_t ADS7142_DWC_HTH_CH1_LSB         = 0x3C;
const uint8_t ADS7142_DWC_LTH_CH1_MSB         = 0x3F;
const uint8_t ADS7142_DWC_LTH_CH1_LSB         = 0x3E;
const uint8_t ADS7142_DWC_HYS_CH1             = 0x41;
//  page 58,59
const uint8_t ADS7142_PRE_ALT_MAX_EVENT_COUNT = 0x36;
const uint8_t ADS7142_ALERT_TRIG_CHID         = 0x03;
const uint8_t ADS7142_ALERT_LOW_FLAGS         = 0x0C;
const uint8_t ADS7142_ALERT_HIGH_FLAGS        = 0x0E;


//  -- END OF FILE --


