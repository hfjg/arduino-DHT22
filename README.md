DHT22
=====

An Arduino library for reading the DHT22 temperature and humidity sensor.

Originally written by Mark Ruys, <mark@paracas.nl>.

Reduced to DHT22/AM2302 and inter variabkes to further reduce memory usage,

Features
--------
  - Very low memory footprint
  - Very small code

Usage
-----

```
#include "DHT.h"

DHT dht;

void setup()
{
  Serial.begin(9600);

  dht.setup(2); // data pin 2
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  Serial.print(dht.getHumidity());
  Serial.print("\t");
  Serial.print(dht.getTemperature());
}
```
Also check out the [example] how to read out your sensor. For all the options, see [dht.h][header].

Installation
------------

Place the [DHT][download] library folder in your `<arduinosketchfolder>/libraries/` folder. You may need to create the `libraries` subfolder if its your first library. Restart the Arduino IDE. 

[download]: https://github.com/markruys/arduino-DHT/archive/master.zip "Download DHT library"
[example]: https://github.com/markruys/arduino-DHT/blob/master/examples/DHT_Test/DHT_Test.pde "Show DHT example"
[header]: https://github.com/markruys/arduino-DHT/blob/master/DHT.h "Show header file"

