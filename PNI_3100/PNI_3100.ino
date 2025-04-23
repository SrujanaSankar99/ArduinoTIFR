#include <SPI.h>

#define CS_PIN 10

void setup() {
    Serial.begin(9600);
    pinMode(CS_PIN, OUTPUT);
    digitalWrite(CS_PIN, HIGH);
    SPI.begin();
}

float averageSensorData() {
    uint32_t average = 0;  
    uint32_t sensorValue;

    for (int i = 0; i < 1; i++) {
        digitalWrite(CS_PIN, LOW);
        sensorValue = SPI.transfer16(0x00);
        digitalWrite(CS_PIN, HIGH);
        
        average += sensorValue;
        delay(1000);
    }

    return (float)average / 1;
}

uint32_t readSensorData() {
  return (uint32_t)(averageSensorData());
}

void loop() {
    Serial.println(readSensorData(), HEX);
}
