//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-12-02
// PURPOSE: unit tests for the ADS7142
//          https://github.com/RobTillaart/ADS7142
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)


#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "ADS7142.h"


unittest_setup()
{
    fprintf(stderr, "ADS7142_LIB_VERSION: %s\n", (char *) ADS7142_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_opmode)
{
  assertEqual( 0, MANUAL_CHANNEL0);
  assertEqual( 4, MANUAL_AUTOSEQ);
  assertEqual( 6, AUTOMONITOR_AUTOSEQ);
  assertEqual( 7, HIGH_PRECISION);
}

unittest(test_input_config)
{
  assertEqual( 0, TWO_CHANNEL_SINGLE_END);
  assertEqual( 1, ONE_CHANNEL_SINGLE_END);
  assertEqual( 2, ONE_CHANNEL_DIFFERENTIAL);
}

unittest(test_error_constants)
{
  assertEqual(   0, ADS7142_OK);
  assertEqual(-100, ADS7142_ERROR);
}


unittest(test_constructor)
{
  ADS7142 ads;

  assertEqual(0x18, ads.getAddress());
  asserEqual(ADS7142_OK, ads.getLastError());
}


unittest(test_error_calls)
{
  //  generate errors e.g. channel error.
  assertEqual(1,1);
}



unittest_main()


//  -- END OF FILE --

