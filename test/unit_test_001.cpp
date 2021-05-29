//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-05-29
// PURPOSE: unit tests for the temperature library
//          https://github.com/RobTillaart/TSL235R
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual);               // a == b
// assertNotEqual(unwanted, actual);            // a != b
// assertComparativeEquivalent(expected, actual);    // abs(a - b) == 0 or (!(a > b) && !(a < b))
// assertComparativeNotEquivalent(unwanted, actual); // abs(a - b) > 0  or ((a > b) || (a < b))
// assertLess(upperBound, actual);              // a < b
// assertMore(lowerBound, actual);              // a > b
// assertLessOrEqual(upperBound, actual);       // a <= b
// assertMoreOrEqual(lowerBound, actual);       // a >= b
// assertTrue(actual);
// assertFalse(actual);
// assertNull(actual);

// // special cases for floats
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon
// assertNotEqualFloat(unwanted, actual, epsilon); // fabs(a - b) >= epsilon
// assertInfinity(actual);                         // isinf(a)
// assertNotInfinity(actual);                      // !isinf(a)
// assertNAN(arg);                                 // isnan(a)
// assertNotNAN(arg);                              // !isnan(a)

#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "TSL235R.h"



unittest_setup()
{
}



unittest_teardown()
{
}



unittest(test_constructor)
{
  fprintf(stderr, "VERSION: %s\n", TSL235R_LIB_VERSION);

  TSL235R mysensor;
  assertEqual(635, mysensor.getWavelength() );
  assertEqualFloat(1.0, mysensor.getWaveLengthFactor(), 0.001);
  assertEqualFloat(5.0, mysensor.getVoltage(), 0.001);
  assertEqualFloat(1.0, mysensor.getVoltageFactor(), 0.001);
}


unittest(test_wavelength)
{
  TSL235R mysensor;
  assertEqual(635, mysensor.getWavelength() );
  assertEqualFloat(1.0, mysensor.getWaveLengthFactor(), 0.001);
  fprintf(stderr,"\n");

  for (int wl = 300; wl < 1200; wl += 100)
  {
    mysensor.setWavelength(wl);
    assertEqual(wl, mysensor.getWavelength() );
  }

  for (int wl = 300; wl < 1200; wl += 100)
  {
    mysensor.setWavelength(wl);
    fprintf(stderr, "%d\t %1.3f\n", wl, mysensor.getWaveLengthFactor() );
  }

  mysensor.setWavelength();
  assertEqual(635, mysensor.getWavelength() );
}


unittest(test_voltage)
{
  TSL235R mysensor(2.7);
  assertEqualFloat(2.7, mysensor.getVoltage(), 0.001);
  assertEqualFloat(0.988, mysensor.getVoltageFactor(), 0.001);
  fprintf(stderr,"\n");

  for (float volts = 2.7; volts < 5.5; volts += 0.1)
  {
    mysensor.setVoltage(volts);
    assertEqualFloat(volts, mysensor.getVoltage(), 0.001);
  }

  for (float volts = 2.7; volts < 5.5; volts += 0.1)
  {
    mysensor.setVoltage(volts);
    fprintf(stderr, "%1,1f\t %1.3f\n", volts, mysensor.getVoltageFactor() );
  }

  mysensor.setVoltage();
  assertEqualFloat(5.0, mysensor.getVoltage(), 0.001);
}


unittest(test_conversion1)
{
  TSL235R mysensor;
  assertEqualFloat(1.0, mysensor.getVoltageFactor(), 0.001);
  assertEqualFloat(1.0, mysensor.getWaveLengthFactor(), 0.001);
  fprintf(stderr,"\n");

  for (uint32_t Hz = 10; Hz < 1000000; Hz *= 2)
  {
    float rad = mysensor.irradiance(Hz);
    assertEqualFloat(0.00142 * Hz, mysensor.irradiance(Hz), 0.001);
  }
}


unittest(test_conversion2)
{
  TSL235R mysensor;
  assertEqualFloat(1.0, mysensor.getVoltageFactor(), 0.001);
  assertEqualFloat(1.0, mysensor.getWaveLengthFactor(), 0.001);
  fprintf(stderr,"\n");

  for (uint32_t Hz = 10; Hz < 1000000; Hz *= 2)
  {
    float rad1 = mysensor.irradiance(Hz);
    float rad2 = mysensor.irradiance(Hz * 10, 10000);  // 10 seconds 10 times as many pulses
    assertEqualFloat(rad1, rad2, 0.001);
  }

  fprintf(stderr, "\ndone...");
}


unittest_main()


// --------
