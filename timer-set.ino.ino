void setup() {
  

}

void loop() {
  

}
#include <Wire.h>

#define SD2403_ADDRESS 0x32

uint8_t decToBcd(uint8_t val) {
  return (val / 10 * 16) + (val % 10);
}

void setup() {
  Wire.begin();

  
  uint8_t secunde = 0;
  uint8_t minute = 0;
  uint8_t ora = 15;

  Wire.beginTransmission(SD2403_ADDRESS);
  Wire.write(0x00); 
  Wire.write(decToBcd(secunde));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(ora));
  Wire.endTransmission();
}

void loop() {
 
}