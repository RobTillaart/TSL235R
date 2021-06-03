//
//    FILE: TSL235R_non_interrupt.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo polling
//    DATE: 2021-06-03

//
// Digital Pin layout ARDUINO
// =============================
//  2 - to TSL235R
// 
// PIN 1 - GND
// PIN 2 - VDD - 5V
// PIN 3 - SIGNAL
//


#include "TSL235R.h"


TSL235R  mySensor;

uint16_t cnt = 0;
uint32_t start = 0;
uint32_t duration = 0;


///////////////////////////////////////////////////////////////////
//
// SETUP
//
void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  pinMode(2, INPUT_PULLUP);
  mySensor.setWavelength(450);
}


void loop()
{
  cnt = 0;
  start = micros();
  while (cnt < 50000)
  {
    while (digitalRead(2) == HIGH);  // wait for LOW
    cnt++;
    while (digitalRead(2) == LOW);   // wait for HIGH
  }
  duration = micros() - start;
  float freq = (1e6 * cnt) / duration;
  Serial.print("FREQ:\t");
  Serial.println(freq, 4);

  Serial.print("irradiance:\t");
  Serial.print(mySensor.irradiance(cnt * 1000, duration));
  Serial.println(" uW/cm2");

}

// -- END OF FILE --
