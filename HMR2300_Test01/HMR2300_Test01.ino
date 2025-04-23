#include <SoftwareSerial.h>
#include <stdlib.h>
#define SERIAL_RX_BUFFER_SIZE 128
// Define software serial pins for RS-232 communication
SoftwareSerial HMR2300(10, 11); // RX, TX
//int size = 3;
//float* c = (float*)malloc(size*sizeof(float));
char c;

//char buffer[128];


void setup() {
    Serial.begin(9600,SERIAL_8N1); // For debugging on Serial Monitor
    HMR2300.begin(9600); // Initialize HMR2300 communication
    delay(100);
    
    Serial.println("HMR2300 Magnetometer Initialized");
    delay(100);
}

// void loop() {
// if (HMR2300.available()) {
//         int index = 0;
//         while (HMR2300.available() && index < sizeof(buffer) - 1) {
//             buffer[index++] = HMR2300.read();
//         }
//         buffer[index] = '\0'; // Null-terminate the string

//         // Parse the buffer assuming data is comma-separated, e.g., "X,Y,Z"
//         char* token = strtok(buffer, ",");
//         float x = atof(token);
//         token = strtok(NULL, ",");
//         float y = atof(token);
//         token = strtok(NULL, ",");
//         float z = atof(token);

//         Serial.print("Timestamp: ");
//         Serial.print(millis());
//         Serial.print(" ms, X: ");
//         Serial.print(x, 9);
//         Serial.print(" G, Y: ");
//         Serial.print(y);
//         Serial.print(" G, Z: ");
//         Serial.println(z);

//         delay(100); // Add delay for stability
//     }
//     }
void loop() {
   if (HMR2300.available()) {
       //String data = "";
       while (HMR2300.available()) {
            c = HMR2300.read();
           //data += c;
       }
       
       Serial.print("HMR2300 Data: ");
       Serial.print(millis()); // Timestamp
       Serial.print(",");
       double data = atof(c);
       Serial.println(data*150000, 6); // Print the received magnetometer data
       
       //delay(100); // Add a small delay for stability
   }
}
