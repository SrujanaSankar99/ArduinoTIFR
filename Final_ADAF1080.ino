#define CS_PIN 10
#define A1_PIN 8
#define AD_PIN 7
#define FD_PIN 5

#include <SPI.h>

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

void flipDriver(){
  digitalWrite(FD_PIN,HIGH);
}

void setup() {
    Serial.begin(9600); 
    
    pinMode(AD_PIN, OUTPUT);
    pinMode(A1_PIN, OUTPUT);
    pinMode(CS_PIN, OUTPUT);
    pinMode(FD_PIN, OUTPUT);
    
    SPI.begin();
    
    setGain(80);
    //flipDriver();
}

float averageSensorData() {
    uint32_t average = 0;  
    uint16_t first16Bits;
    uint8_t lastByte;
    uint32_t sensorValue;

    for (int i = 0; i < 1000; i++) {
        digitalWrite(CS_PIN, LOW);
        first16Bits = SPI.transfer16(0x00);
        lastByte = SPI.transfer(0x00); 
        digitalWrite(CS_PIN, HIGH);

        sensorValue = ((uint32_t)first16Bits << 2) | ((lastByte >> 6) & 0x03);
        
        average += sensorValue;
        delay(1);
    }

    return (float)average / 1000.0;
}

uint32_t readSensorData() {
  return (uint32_t)(averageSensorData());
}

int counts(){
  int sensorValue = averageSensorData();
  int diff = sensorValue - 128747;
  return diff;
}

float readVoltData() {
    float sensorValue = averageSensorData();
    float milliVolt = sensorValue / 52.4288;     //52428.8 = 2^18/5 (total no. of bytes/ total amount of voltage supplied)
    return milliVolt;
}

float readTeslaData() {
    float milliVolt = readVoltData();
    float milliTesla = (milliVolt/8);   //183
    return milliTesla;
}

void loop() {    
    Serial.println(readSensorData()); //for 18 bit code
    //Serial.println(counts());
    //Serial.print(readVoltData(), 9);  //for volt
    //Serial.println(" mV");
    //Serial.print(readTeslaData(), 3); //for nano tesla
    //Serial.println(" mT");
}