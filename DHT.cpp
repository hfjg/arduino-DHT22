/******************************************************************
  Minimal integer based DHT Temperature & Humidity Sensor library for Arduino.

  Features:
  - Very low memory footprint
  - Very small code

  https://github.com/hfjg/arduino-DHT22
  Written by Hermann Gebhard, h-gebhard@web.de

  forked from 
  https://github.com/markruys/arduino-DHT
  by Mark Ruys, mark@paracas.nl.

  BSD license, check license.txt for more information.
  All text above must be included in any redistribution.

  Datasheets:
  - http://www.adafruit.com/datasheets/DHT22.pdf
  - http://meteobox.tk/files/AM2302.pdf

  Changelog:
   2020-03-02: Reduced lib to minimum, changed to integer arithmetics
   2013-07-01: Add a resetTimer method
   2013-06-12: Refactored code
   2013-06-10: Initial version
 ******************************************************************/

#include "DHT.h"

void DHT::setup(uint8_t pin)
{
  DHT::pin = pin;
  DHT::lastReadTime = millis() - 3000;
}

uint8_t DHT::readSensor(uint32_t *result)
{
  static union{
    uint32_t r32;
    struct {
      int16_t temp, humi;
    }ht;
  }conversionResult;
  
  uint16_t rawTemperature, rawHumidity;
  uint16_t data = 0;
  unsigned long startTime = millis();

  // Make sure we don't poll the sensor too often
  // - Max sample rate DHT22 is 0.5 Hz (duty cicle 2000 ms)

  if ( (unsigned long)(startTime - lastReadTime) < 1999L) {
    *result = conversionResult.r32;
    return ERROR_NO_NEW_SAMPLE;
  }

  // Request sample
  lastReadTime = startTime;

  digitalWrite(pin, LOW); // Send start signal
  pinMode(pin, OUTPUT);
  delayMicroseconds(800);
  
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH); // Switch bus to receive data

  // We're going to read 83 edges:
  // - First a FALLING, RISING, and FALLING edge for the start bit
  // - Then 40 bits: RISING and then a FALLING edge per bit
  // To keep our code simple, we accept any HIGH or LOW reading if it's max 85 usecs long

  for ( int8_t i = -3 ; i < 2 * 40; i++ ) {
    byte age;
    startTime = micros();

    do {
      age = (unsigned long)(micros() - startTime);
      if ( age > 90 ) {
        return ERROR_TIMEOUT;;
      }
    }
    while ( digitalRead(pin) == (i & 1) ? HIGH : LOW );

    if ( i >= 0 && (i & 1) ) {
      // Now we are being fed our 40 bits
      data <<= 1;

      // A zero max 30 usecs, a one at least 68 usecs.
      if ( age > 30 ) {
        data |= 1; // we got a one
      }
    }

    if (i==31){
        rawHumidity = data;
    }
    else if (i==63){
        rawTemperature = data;
        data = 0;
    }
  }

  // Verify checksum

  if ( (byte)(((byte)rawHumidity) + (rawHumidity >> 8) + ((byte)rawTemperature) + (rawTemperature >> 8)) != data ) {
    return ERROR_CHECKSUM;;
  }

  // Pack readings into conversionResult
  if ( rawTemperature & 0x8000 ) {
    rawTemperature = -(int16_t)(rawTemperature & 0x7FFF);
  }
  conversionResult.ht.humi = rawHumidity;
  conversionResult.ht.temp = rawTemperature;
  *result = conversionResult.r32;

  return ERROR_NONE;
}
