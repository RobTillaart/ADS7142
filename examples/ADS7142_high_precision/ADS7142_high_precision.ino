//
//    FILE: ADS7142_test
//  AUTHOR: Rob Tillaart
// PURPOSE: test ADS7142 library
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
  //  set mode
  ads.setHighPrecision();
  ads.setDataFormat(ADD_ZEROS);
}


void loop()
{
  //  fetch in pairs.
  if (ads.getDataBufferCount() >= 2)
  {
    uint16_t value[2];
    ads.read(value, 2);
    Serial.print(0);
    Serial.print('\t');
    Serial.println(value[0]);
    Serial.print(1);
    Serial.print('\t');
    Serial.println(value[1]);
  }
  //  other tasks ..
}



//  -- END OF FILE --
