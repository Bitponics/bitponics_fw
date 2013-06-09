#define BLUE_PIN 10
#define GREEN_PIN 11
#define RED_PIN 12

void setupLedPins(){
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT); 
}


void setColor(const byte rgb[]){
  analogWrite(RED_PIN, rgb[0]);
  analogWrite(GREEN_PIN, rgb[1]);
  analogWrite(RED_PIN, rgb[2]);
  //delay(2000);
}


