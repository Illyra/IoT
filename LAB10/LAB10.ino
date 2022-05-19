#include <Wire.h>
#include <SPI.h>
//#include <SD.h>
//File myfile;


//unsigned long runMillis;
const int MPU6050_addr = 0x68;
int16_t AccX, AccY, AccZ, Temp, GyroX, GyroY, GyroZ;


void setup()
{
  Wire.setClock(400000);
  Wire.begin();
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  delay(10000);

//  Serial.print("Initializing SD CARD....");
//
//  if (!SD.begin(4))
//  {
//    Serial.println("Initializiation failed!");
//    while (1);
//   }
//  Serial.println("Initialization done..");
//
//  SD.remove("log.txt");
//
//  myfile = SD.open("log.txt", FILE_WRITE);
//  if (!myfile)
//  {
//    Serial.println("Error Opening File");
//  }
//  myfile.close();
}

void loop()
{
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr, 14, true);
  AccX = Wire.read() << 8 | Wire.read();
  AccY = Wire.read() << 8 | Wire.read();
  AccZ = Wire.read() << 8 | Wire.read();
 // Temp = Wire.read() << 8 | Wire.read();
  GyroX = Wire.read() << 8 | Wire.read();
  GyroY = Wire.read() << 8 | Wire.read();
  GyroZ = Wire.read() << 8 | Wire.read();
  Serial.print("AccX= "); Serial.print(AccX);
  Serial.print(" | | AccY= "); Serial.print(AccY);
  Serial.print(" | | AccZ= "); Serial.print(AccZ);
  Serial.print(" | | GyroX= "); Serial.print(GyroX);
  Serial.print(" | | GyroY= "); Serial.print(GyroY);
  Serial.print(" | | GyroZ= "); Serial.print(GyroZ);
  Serial.print('\n');

//  myfile = SD.open("log.txt", FILE_WRITE);
//  if (myfile)
//  {
//    myfile.print(AccX);
//    myfile.print("\t");
//    myfile.print(AccY);
//    myfile.print("\t");
//    myfile.print(AccZ);
//    myfile.print("\t");
//    myfile.print(GyroX);
//    myfile.print("\t");
//    myfile.print(GyroY);
//    myfile.print("\t");
//    myfile.print(GyroZ);
//    myfile.print("\t");
//    runMillis = millis();
//    myfile.println(runMillis);
//  }
//  myfile.close();

  delay(100);
}
