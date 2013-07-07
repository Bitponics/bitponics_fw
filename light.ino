#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561.h>
#define LUX_SDA 20
#define LUX_SCL 21

Adafruit_TSL2561 tsl = Adafruit_TSL2561(TSL2561_ADDR_FLOAT, 12345);

//-------------------------------------------------------
void setupLight(){

  if(!tsl.begin()){
    Serial.print("no lux sensor detected");
    while(1);
  }
  else Serial.println("- lux Sensor");

  tsl.enableAutoGain(true);          /* Auto-gain ... switches automatically between 1x and 16x */
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);      /* fast but low resolution */

}

//-------------------------------------------------------
float getLight(){
  /* Get a new sensor event */
  int tempInt;
  sensors_event_t event;
  
  while(tempInt<=0){
    tsl.getEvent(&event);
    tempInt = event.light;
    errors ++;
    if(errors>5){
      Serial.println("Lux error, reseting");
      resetBoard();
    }
    delay(10);
  }
  
  return tempInt;


}
//-------------------------------------------------------


