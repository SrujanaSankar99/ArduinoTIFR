#include <Wire.h>
#include <Adafruit_ADS1X15.h>


Adafruit_ADS1115 ads;


void setup() {
  Serial.begin(9600);
  ads.setGain(GAIN_TWOTHIRDS);
  ads.begin();
}


void loop() {
  int16_t adc0 = ads.readADC_SingleEnded(0);  // Read A0 unsigned data
  float voltage = adc0 * 0.100708 / 1000;
  // conversion factor 3.3/2^15 (total voltage supplied)



  Serial.print(adc0);
  Serial.print("\t");
  Serial.print(voltage, 4);
  Serial.println(" V");


  delay(500);
}
