//
//    FILE: ADS7142_automatic_2channel
//  AUTHOR: Rob Tillaart
// PURPOSE: demo ADS7142
//     URL: https://github.com/RobTillaart/ADS7142


#include "Arduino.h"
#include "ADS7142.h"

ADS7142 ads;

uint32_t lastTime = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ADS7142_LIB_VERSION: ");
  Serial.println(ADS7142_LIB_VERSION);
  Serial.println();

  Wire.begin();

  ads.begin();
  //  set auto monitoring and auto sequence
  ads.setAutoMonitoringAutoSequencing();
  ads.setDataFormat(ADD_CHANNEL_VALID_BIT);
}


void loop()
{
  uint8_t n = ads.getDataBufferCount();
  for (int i = 0; i < n; i++)
  {
    uint16_t value = ads.read();
    uint8_t channel = (value & 0x0002) >> 1;
    uint8_t valid = (value & 0x0001);
    //  strip off extra bits.
    value &= 0xFFF0;

    Serial.print(channel);
    Serial.print('\t');
    Serial.print(valid);
    Serial.print('\t');
    Serial.println(value);
  }
  Serial.println();
  delay(2000);
}


//  -- END OF FILE --
