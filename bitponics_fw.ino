//global includes
#include <Wire.h>
#include "customDataTypes.h"
#include <avr/wdt.h>

const byte RED[] = {
  255, 0,0};
const byte YELLOW[] = {
  255, 255,0};
const byte ORANGE[] = {
  255,124,0};
const byte BLUE[] = {
  0,0,255};
const byte GREEN[] = {
  0,0,255};
const byte PURPLE[] = {
  255,0,255};
  

#define RESET 7
#define WIFI_RESET 38
#define BUTTON A2

char buf[80];
long timeout;
unsigned long reset_time = 1200000; //20 minutes for reset
unsigned long requestCount = 0;
boolean terminalMode;

void setup() {
  setupLED();

  digitalWrite(WIFI_RESET, HIGH);
  digitalWrite(RESET, HIGH);
  pinMode(RESET, OUTPUT);
  setupRelays();
  

  pinMode(BUTTON, INPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println(F("**********************"));
  Serial.println(F("-> Device Boot"));

  setupSensors(38400);
  setupWifi(9600);
  setupWDT();

}

void loop(){

  checkBtn();

  if(!terminalMode) wifiLoop();

  if(millis()>reset_time) resetBoard();

}

void setupSensors(unsigned int DATABAUD){
  Serial.println("-> Initalizing sensors");
  setupTemps();
  setupLight();
  setupEc(DATABAUD);
  setupPh(DATABAUD);
}


//void terminal(){
//
//  while(Serial1.available() > 0) {
//    Serial.write(Serial1.read());
//  }
//
//  if(Serial.available()) {
//    Serial1.write(Serial.read());
//  }
//
//}

void resetBoard(){
  //wdt_enable(WDTO_8S); 
  Serial.println("-> Board timed reset");
  wdt_enable(WDTO_30MS); 
  delay(1000);
}

void setupWDT() {
  cli();
  MCUSR = 0;
  WDTCSR |= B00011000;
  WDTCSR = B01000111;
  sei();
}

void SerialEvent(){
  if(!terminalMode){
    Serial.readBytesUntil('\r', buf, 5);
    if(buf == "exit"){
      terminalMode = false; 
    }
    if(buf == "$$$"){
      terminalMode = true;
      Serial1.write("$$$"); 
    }
  }
  else{
    Serial1.write(Serial.read());
  }
}

void SerialEvent1(){
  if(terminalMode){ 
    Serial.write(Serial1.read());
  }

}

ISR(WDT_vect){
  Serial.println("~~~");
  if(millis()-timeout > 45000 && requestCount > 0){
    resetBoard(); 
  }
}

//void logMsg(int type, String msg){
//  switch(type){
//    case SENSOR:
//    Serial.print("-");
//    Serial.println(msg);
//    break;
//  }
//  
//  
//}


String tempChar(float t, char* buf){
  char* c = dtostrf(t,5,2,buf);
  return c;
}






