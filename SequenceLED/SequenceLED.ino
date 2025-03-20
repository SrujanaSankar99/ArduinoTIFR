int timer = 50;
int ledPins[] = {

  8,8
};      
int pinCount = 6;     

void setup() {

  for (int thisPin = 0; thisPin < pinCount; thisPin++) {

    pinMode(ledPins[thisPin], OUTPUT);

  }
}

void loop() {

  for (int thisPin = 0; thisPin < pinCount; thisPin++) {

    digitalWrite(ledPins[thisPin], HIGH);

    delay(timer);

    digitalWrite(ledPins[thisPin], LOW);

  }

  for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--) {

    digitalWrite(ledPins[thisPin], HIGH);

    delay(timer);

    digitalWrite(ledPins[thisPin], LOW);

  }
}