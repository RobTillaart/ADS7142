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
}


void loop()
{
}


//  -- END OF FILE --
