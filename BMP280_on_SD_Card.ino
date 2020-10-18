#include <Wire.h>
#include "SparkFunBME280.h"
BME280 mySensorA;

#include <SD.h>
File myFile;


void setup() {
   Serial.begin(9600);
   
   Wire.begin();
   mySensorA.setI2CAddress(0x76);

   if(mySensorA.beginI2C() == false) Serial.println("Sensor A connect failed");
   while(!Serial){
   pinMode(10,OUTPUT); }

   if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  //READING FROM FILE
  /*
   myFile = SD.open("BME280.TXT", FILE_READ);
   if(myFile)
   {
   Serial.println("Reading from BME280.TXT");
    while(myFile.available()){
        Serial.write(myFile.read());
      }
      myFile.close();
   }
  */
}

void loop() {
 myFile = SD.open("BME280.txt", FILE_WRITE);
  if(myFile)
  {
    myFile.print("Temperature= ");
    myFile.print(mySensorA.readTempC());
    myFile.println("*C");
    Serial.print("Temperature = ");
    Serial.print(mySensorA.readTempC());
    Serial.println(" *C");

    myFile.print("Pressure= ");
    myFile.print(mySensorA.readFloatPressure());
    myFile.println(" Pa");
    Serial.print("Pressure = ");
    Serial.print(mySensorA.readFloatPressure());
    Serial.println(" Pa");

    myFile.print("Approx altitude= ");
    myFile.print(mySensorA.readFloatAltitudeFeet()*0.34);
    myFile.println(" m");
    Serial.print("Approx altitude = ");
    Serial.print(mySensorA.readFloatAltitudeFeet()*0.34); // this should be adjusted to your local forcase
    Serial.println(" m");

    myFile.println();
    Serial.println();
    delay(2000);
    
    myFile.close();
    }  
}
