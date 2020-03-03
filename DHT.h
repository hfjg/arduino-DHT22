/******************************************************************
  DHT22 Temperature & Humidity Sensor library for Arduino.

  Features:
  - Very low memory footprint
  - Very small code

  http://www.github.com/hfjg/arduino-DHT22

  Written by Hermann Gebhard, h-gebhard@web.de
  forked from Mark Ruys, mark@paracas.nl.

  BSD license, check license.txt for more information.
  All text above must be included in any redistribution.

  Datasheets:
  - http://www.adafruit.com/datasheets/DHT22.pdf
  - http://meteobox.tk/files/AM2302.pdf

  Changelog:
   2020-03-02: Cut down and rewritten to integer arithmetics
   2013-07-01: Add a resetTimer method
   2013-06-12: Refactored code
   2013-06-10: Initial version
 ******************************************************************/

#ifndef dht_h
#define dht_h

#if ARDUINO < 100
  #include <WProgram.h>
#else
  #include <Arduino.h>
#endif

class DHT
{
public:

  typedef enum {
    ERROR_NONE = 0,
    ERROR_TIMEOUT,
    ERROR_CHECKSUM,
    ERROR_NO_NEW_SAMPLE
  }
  DHT_ERROR_t;

  void setup(uint8_t pin);
  uint8_t readSensor(uint32_t *result);

protected:
  uint8_t pin;

private:
  unsigned long lastReadTime;
};

#endif /*dht_h*/
