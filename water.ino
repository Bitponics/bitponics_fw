#define SERIESRESISTOR 2000    
#define SENSORPIN A6 
float height;
float range = 220;
float minVal = 190;
float maxHeight = 21;
//boolean waterLevel = false;

//-----------------------------------------------------------------------------------------
//init ph by making sure we can communicate
void setupPh(unsigned int DATABAUD){
  
 Serial2.begin(DATABAUD);
 Serial2.setTimeout(6000);
 Serial2.print("L0\r");
 delay(20);
 Serial2.print("L0\r");
 delay(500);
 //Serial2.print("L1\r");
 Serial.println("- pH");
 
}
//-----------------------------------------------------------------------------------------
//function to ask for pH and return as float
float getPh(float _c){
 //Serial.println("R\\r --> PH"); //let us know we are asking
 Serial2.print(_c);
 Serial2.write('\r'); //ask device
 delay(500);
 return Serial2.parseFloat(); //return data as float
}

//-----------------------------------------------------------------------------------------
void setupEc(unsigned int DATABAUD){
 
 Serial3.begin(DATABAUD);
 Serial3.setTimeout(6000);
 Serial3.print("L1\r");
 delay(100);
 Serial3.print("L0\r");
 delay(100);
 //Serial3.print("L1\r");
 // Set EC to K 0.1
 Serial3.print("P,1\r"); // set sensor type K
 Serial3.flush();
 Serial.println("- EC");
}

//-----------------------------------------------------------------------------------------
int getEc(float _c){
 //Serial.println("R\\r --> EC"); //let us know we are asking
 Serial3.print(_c);
 Serial3.print("\r"); //ask device
 delay(500);
 
 int ec = Serial3.parseInt();
 Serial3.parseInt();  // discard other readings
 Serial3.parseFloat();
 
 return ec;
 
}

float getWaterLevel(){
 
  int reading = analogRead(SENSORPIN);
  height = maxHeight-(reading-minVal)/range*maxHeight;
  return height;
}


