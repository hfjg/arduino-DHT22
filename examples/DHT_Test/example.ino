#include "DHT.h"

DHT dht;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(F("Starting Test"));

  dht.setup(2);  
}

void loop() {
  uint32_t result;
  uint8_t err;

  // readout sensor
  err = dht.readSensor(&result);

  // show results
  Serial.print(F("\n\nErrorCode:      ")); Serial.print(err);
  Serial.print(F("\nHumidity*10:    ")); Serial.print( (result>>16) & 0xFFFF );
  Serial.print(F("\nTemperature*10: ")); Serial.print( result & 0xFFFF);
  delay(2500);

}
