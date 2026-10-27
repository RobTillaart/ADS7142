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


unittest(test_constants)
{
  assertEqualFloat(1, 1, 0.001);
}


unittest_main()


//  -- END OF FILE --

