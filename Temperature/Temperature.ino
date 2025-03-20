int temp = 50;
int myDelayNum = 1000;

void setup() {
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

}

void loop() {
  if(temp>50){
    digitalWrite(6, HIGH);
    delay(myDelayNum);
    digitalWrite(6, LOW);
    delay(myDelayNum);
  }
  else if(temp>=10 && temp<=50){
    digitalWrite(7, HIGH);
    delay(myDelayNum);
    digitalWrite(7, LOW);
    delay(myDelayNum);
  }
  else{
    digitalWrite(8, HIGH);
    delay(myDelayNum);
    digitalWrite(8, LOW);
    delay(myDelayNum);
  }

}
