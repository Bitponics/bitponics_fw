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

unsigned long reset_time = 1200000; //20 minutes for reset

void setup() {
  
  digitalWrite(WIFI_RESET, HIGH);
  digitalWrite(RESET, HIGH);
  pinMode(RESET, OUTPUT);
  setupRelays();
  setupLedPins();

  pinMode(BUTTON, INPUT);
  //attachInterrupt(0, reset, RISING);

  /* these are the required BAUDS for scan to work */
  Serial.begin(115200);
    Serial.println();
  Serial.println(F("**********************"));
  Serial.println(F("-> Device Boot"));
  setColor(RED);
  
  setup_sensors(38400);
  wifiSetup(9600);

}

void loop(){

  wifiLoop();
  terminal();
  //if(millis()>reset_time) resetBoard();
}

void setup_sensors(unsigned int DATABAUD){
  Serial.println("-> Initalizing sensors");
  setup_temps();
  setup_light();
  setup_ec(DATABAUD);
  setup_ph(DATABAUD);
}


void terminal(){

  while(Serial1.available() > 0) {
    Serial.write(Serial1.read());
  }

  if(Serial.available()) {
    Serial1.write(Serial.read());
  }

}

void reset(){
  //wdt_enable(WDTO_8S); 
  wdt_enable(WDTO_30MS); 
  delay(1000);
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
