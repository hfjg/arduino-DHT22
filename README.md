DHT22
=====

A highly reduced Arduino library for reading the DHT22 temperature and humidity sensor.

The library uses only integer calculations, making it much smaller and faster, thus usable 
even on tiny AVR. The conversion result is passed as one 32-Bit-variable. The upper 16 bit
(uint16_t) hold the relative humidity in multiples of 0.1%. The lower 16 bit (int16_t)
hold the temperature in tenth of centigrades.

Author: Hermann Gebhard, <h-gebhard@web.de>
Originally written by Mark Ruys, <mark@paracas.nl>.

Features
--------
  - No floats used
  - Very low memory footprint
  - Very small code

For usage check out the example how to read out your sensor. 

Installation
------------

Place the library folder in your `<arduinosketchfolder>/libraries/` folder. You may need to create the `libraries` subfolder if its your first library. Restart the Arduino IDE. 
