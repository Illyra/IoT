#include <SPI.h>
#include <SD.h>
File myfile;

int temppin = A0;
unsigned long runMillis;
float tempF;
double thermoresist;


void setup() {
  Serial.begin(9600);
  pinMode (temppin, INPUT);

  Serial.print("Initializing SD CARD....");

  if(!SD.begin(4))
  {
    Serial.println("Initializiation failed!");
    while(1);
  }
  Serial.println("Initialization done..");

  SD.remove("log.txt");

  myfile = SD.open("log.txt", FILE_WRITE);
  if(myfile)
  {
    myfile.println("Temp(C)\tResistance(ohm)\\t\tRUNTIME");
  }
  else
  {
    Serial.println("Error Opening File");
  }
  myfile.close();
}

void loop() {
    int reading = analogRead(temppin);
    double thermoresist = 10000.0 * ((1024.0 / reading - 1));
    double logofthermoresist = log(thermoresist);
    double tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * logofthermoresist * logofthermoresist)) * logofthermoresist);
    float tempC = tempK - 273.15;
    float tempF = (tempC * 9.0) / 5.0 + 32.0;

    Serial.print(tempC);
    Serial.print('\t');
    Serial.print(thermoresist);
    Serial.print('\t');
    //Serial.print(tempF);
    //Serial.print('\n');
    runMillis = micros();
    Serial.println(runMillis);

    myfile = SD.open("log.txt", FILE_WRITE);
    {
      myfile.print(tempC);
      myfile.print('\t');
      myfile.print(thermoresist);
      myfile.print('\t');
      myfile.println(runMillis);
    }
    myfile.close();
    delay(1000);

}
