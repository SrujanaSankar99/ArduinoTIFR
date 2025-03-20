//LED variables
int LED_port = 7;
int timer = 10;

//Photoresistor variables
int photo_port = A0;        //analog port
const int threshold = 100;     //min amount of light that reaches the photoresistor( 50 - off, 150 - on)
unsigned long lastChangeTime = 0;
int ledFrequency = 0;   //number of times the LED switches on
unsigned long lastUpdateTime = 0;
unsigned long updateInterval = 1000;  // updating every second
int lightLevel = 0;
//float time_period;

void setup()
{
  pinMode(LED_port, OUTPUT);
  Serial.begin(9600);
  pinMode(photo_port, INPUT);
}

void loop()
{
  lightLevel = analogRead(photo_port);
  //Serial.println(lightLevel);
  
  
  digitalWrite(LED_port, HIGH);
  delay(timer);
  digitalWrite(LED_port, LOW);
  delay(timer);
  
  if (lightLevel > threshold) {     //checking if the light received by the photoresistor is greater than the threshold value
    if (millis() - lastChangeTime > 0) {
      ledFrequency++;
      lastChangeTime = millis();
    }
  }

  if (millis() - lastUpdateTime >= updateInterval) {
    Serial.print("LED Frequency: ");
    Serial.println(ledFrequency);
    /*time_period = 1/ledFrequency;
    Serial.print("Time period: ");
    Serial.println(time_period);*/
    ledFrequency = 0;
    lastUpdateTime = millis();
  }
}