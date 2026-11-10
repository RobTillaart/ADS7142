//
//    FILE: ADS7142_manual_autosequence
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
  //  set manual mode
  ads.setManualAutoSequencing();
  ads.startSequence();
}


void loop()
{
  uint16_t value = ads.read();
  Serial.println(value);
  delay(1000);
}


//  -- END OF FILE --
