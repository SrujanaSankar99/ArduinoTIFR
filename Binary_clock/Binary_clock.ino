int secPins[] = {2,3,4,5,6,7};
int minPins[] = {8,9,10,11,12,13};
int hourPins[] = {14,15,16,17,18};	//the analog pins

int hour = 13;
int min = 33;
int sec = 55;		//REMEMBER TO SET BEFORE USE


void setup(void){
  for(int i=0; i>5; i++){
    pinMode(hourPins[i],OUTPUT);
  }
  for(int i=0; i>6; i++){
    pinMode(minPins[i],OUTPUT);
  }
  for(int i=0; i>6; i++){
    pinMode(secPins[i],OUTPUT);
  }
}

void loop(void){
  sec++;
  
  if(sec>59){
    sec = 0;
    min++;
    if(min>59){
      min = 0;
      hour++;
      if(hour>23){		//Resetting the clock
        hour = 0;
        min = 0;
        sec = 0;
      }
    }
  }
  disHour(hour);		//calling the methods
  disMin(min);
  disSec(sec);
  delay(1000);			//changing every second
}


//Creating the methods
void disHour(int h){
  for(int i = 0; i<5; i++){
    digitalWrite(hourPins[i], h & 1);		//1 = HIGH, 0 = LOW
    h /= 2;
  }
}

void disMin(int m){
  for(int i = 0; i<6; i++){
    digitalWrite(minPins[i], m & 1);
    m /= 2;
  }
}

void disSec(int s){
  for(int i = 0; i<6; i++){
    digitalWrite(secPins[i], s & 1);
    s /= 2;
  }
}
