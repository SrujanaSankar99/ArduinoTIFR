/*
Pins for controlling the gain
11(high high) = 80
10(high low) = 40
00(low low) = 20
*/

#define AD_PIN 7  // Gain Control Bit 0
#define A1_PIN 8  // Gain Control Bit 1
#define CS_PIN 10 // CSI (chip select for SPI communication) pin attached to pin 10

#include <SPI.h> // internal package for SPI communication

void setGain(int gain) {
    switch (gain) {
        case 20:
            digitalWrite(AD_PIN, LOW);
            digitalWrite(A1_PIN, LOW);
            break;
        case 40:
            digitalWrite(AD_PIN, HIGH);
            digitalWrite(A1_PIN, LOW);
            break;
        case 80:
            digitalWrite(AD_PIN, HIGH);
            digitalWrite(A1_PIN, HIGH);
            break;
    }
    Serial.print("Gain set to: ");
    Serial.println(gain);
}

void setup() {
    Serial.begin(9600); // 115200 is supposed to be faster but didn't work for some reason. Need to investigate further
    
    pinMode(AD_PIN, OUTPUT);
    pinMode(A1_PIN, OUTPUT);
    pinMode(CS_PIN, OUTPUT);
    
    SPI.begin();
    
    // Setting gain, change if needed
    // 80 > 40 > 20 precision, kind of like how it works in audio
    setGain(40);
}

uint32_t readSensorData() {
    // uint16_t unsigned int, need to see what will happen if it is signed
    uint16_t first16Bits;
    uint8_t lastByte;
    uint32_t sensorValue;

    digitalWrite(CS_PIN, LOW);   // starts the SPI communication
    first16Bits = SPI.transfer16(0x00); // Sending dummy data to receive actual data (works in exchange kind of way)
    lastByte = SPI.transfer(0x00); // Read last 8 bits, but only top 2 bits matter
    digitalWrite(CS_PIN, HIGH);   // stops the communication

    // Extract the full 18-bit value
    sensorValue = ((uint32_t)first16Bits << 2) | ((lastByte >> 6) & 0x03);  // 00000011 * lastByte will get the last 2 digits only, OR operator that merges both the numbers

    return sensorValue;

}

float readVoltData() {
    // uint16_t unsigned int, need to see what will happen if it is signed
  uint16_t first16Bits;
  uint8_t lastByte;
  uint32_t sensorValue;

  digitalWrite(CS_PIN, LOW);   //2 starts the SPI communication
  first16Bits = SPI.transfer16(0x00); // Sending dummy data to receive actual data (works in exchange kind of way)
  lastByte = SPI.transfer(0x00); // Read last 8 bits, but only top 2 bits matter
  digitalWrite(CS_PIN, HIGH);   // stops the communication

    // Extract the full 18-bit value
  sensorValue = ((uint32_t)first16Bits << 2) | ((lastByte >> 6) & 0x03);  // 00000011 * lastByte will get the last 2 digits only, OR operator that merges both the numbers

  float volt = sensorValue/52428.8;
  return volt;
}

void loop() {    
    Serial.println(readVoltData(), 11);
    //Serial.println(readSensorData());
    delay(250);   // adjust to be quicker if needed after configuration
}
