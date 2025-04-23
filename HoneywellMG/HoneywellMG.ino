#include <SoftwareSerial.h>

SoftwareSerial HMR2300(3, 4); // RX, TX

void setup() {
  Serial.begin(9600);         // Arduino Serial Monitor
  HMR2300.begin(19200);        // HMR2300 via MAX232
  delay(100);
  Serial.println("Sending 'P' command...");
  
  HMR2300.print("P\r");
}

void loop() {
  if (HMR2300.available()) {
    String data = "";
    while (HMR2300.available()) {
      char c = HMR2300.read();
      data += c;
    }

    Serial.print("Raw Data: ");
    Serial.println(data);

    delay(1000);
  }
}

