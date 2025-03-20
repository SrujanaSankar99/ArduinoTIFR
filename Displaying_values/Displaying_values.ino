//Initialisation for the display
  #include <Adafruit_GFX.h>    // Core graphics library
  #include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
  #include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
  #include <SPI.h>

  #if defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
    #define TFT_CS         14
    #define TFT_RST        15
    #define TFT_DC         32

  #elif defined(ESP8266)
    #define TFT_CS         4
    #define TFT_RST        16                                            
    #define TFT_DC         5

  #else
    // For the breakout board, you can use any 2 or 3 pins.
    // These pins will also work for the 1.8" TFT shield.
    #define TFT_CS        10
    #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
    #define TFT_DC         8
  #endif


  // For 1.14", 1.3", 1.54", 1.69", and 2.0" TFT with ST7789:
  Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);


//LED variables
  int LED_port = 7;
  int timer = 100;

//Photoresistor variables
  int photo_port = A0;        //analog port
  const int threshold = 100;     //min amount of light that reaches the photoresistor( 50 - off, 150 - on)
  unsigned long lastChangeTime = 0;
  int ledFrequency = 0;   //number of times the LED switches on
  unsigned long lastUpdateTime = 0;
  unsigned long updateInterval = 1000;  // updating every second
  int lightLevel = 0;

void setup()
{
  pinMode(LED_port, OUTPUT);
  Serial.begin(9600);
  pinMode(photo_port, INPUT);

  tft.init(135, 240);
  //tftPrintTest();
  heading();
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
      //tftPrintTest();
      frequency();
    ledFrequency = 0;
    lastUpdateTime = millis();
  }
}

void heading() {
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(4.5);
  tft.println("LED");
  tft.println("Freq:");
}

void frequency() {
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(8);
  tft.println(ledFrequency);
}

/*void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(4.5);
  tft.println("Freq:");
  tft.println(ledFrequency);
}*/