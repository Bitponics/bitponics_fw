/*-------------------------------------------*
 ONE WIRE
 *-------------------------------------------*/
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 22 //pin
#define TEMPERATURE_PRECISION 12

OneWire onewire(ONE_WIRE_BUS);
DallasTemperature water(&onewire);
DeviceAddress water_temp;

/*-------------------------------------------*
 DTH-22 TEMP/HUM
 *-------------------------------------------*/
#include "DHT.h"
#define DHTPIN 23       // pin
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE);

void setupTemps(){

  dht.begin();
  Serial.println("- DHT");
  water.begin();
  if(!water.getAddress(water_temp,0)){
    Serial.println("Failed to setup water temp sensor");
    resetBoard();
  } 
  else Serial.println("- Water Temp");

}

float getWaterTemp(){
  water.requestTemperatures();
  return water.getTempC(water_temp); 

}

float getAirTemp(){
  errors= 0;
  float t = dht.readTemperature();
  while(isnan(t)){
    errors++;
    if(errors > errMax) {
      Serial.println("temperature read error... reseting!");
      resetBoard(); 
    }
  }
  return t;
}

float getHumidity(){
  float h = dht.readHumidity();
  while(isnan(h)){
    errors++;
    if(errors > errMax) {
      Serial.println("humididty read error... reseting!");
      resetBoard(); 
    }
  }
  return h;
}


