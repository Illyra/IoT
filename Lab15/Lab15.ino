#include <SPI.h>
#include <SD.h>
File myFile;

unsigned long runMillis;
int analogInput_vol = A0;
float vout = 0.0;
float vin = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int svalue = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(analogInput_vol, INPUT);

  Serial.print("Iniatializing SD Card...");

  if(!SD.begin(4))
  {
    Serial.println("initialization failed!");
    while(1);
  }
  Serial.println("Initialization done.");

  SD.remove("log.txt");

  myFile = SD.open("log.txt", FILE_WRITE);
  if (myFile)
  {
    myFile. println("Current(A)\tVoltage(v)\t\tRUNTIME");
  }
  else
  {
    Serial.println("Error opening file");
  }
  myFile.close();

}

void loop() 
{
  svalue = analogRead(analogInput_vol);
  vout = (svalue * 5.0) / 1024.0;
  vin = vout / (R2 /(R2 + R2));

  Serial.print(vin);
  Serial.print("\t");
  runMillis = millis();
  Serial.println(runMillis);

  myFile = SD.open("log.txt", FILE_WRITE);
  if(myFile)
  {
    myFile.print(vin);
    myFile.print("\t");
    myFile.println(runMillis);  
  }
  myFile.close();


}
