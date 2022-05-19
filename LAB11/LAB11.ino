#include <Wire.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>
File myfile;

LiquidCrystal lcd(2, 3, 5, 6, 7, 8);
unsigned long runMillis;
const int MPU6050_addr = 0x68;
int16_t AccX, AccY, AccZ, GyroX, GyroY, GyroZ, Temp;
int counter = 0;

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

  lcd.begin(16,2);
  lcd.setCursor(0,0);

  Serial.print("Initializing SD CARD....");

  if (!SD.begin(4))
  {
    Serial.println("Initializiation failed!");
    while (1);
   }
  Serial.println("Initialization done..");

  SD.remove("log.txt");

  myfile = SD.open("log.txt", FILE_WRITE);
  if (!myfile)
  {
    Serial.println("Error Opening File");
  }
  myfile.close();
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
  Temp = Wire.read() << 8 | Wire.read();
  GyroX = Wire.read() << 8 | Wire.read();
  GyroY = Wire.read() << 8 | Wire.read();
  GyroZ = Wire.read() << 8 | Wire.read();
  unsigned long runMillis = millis();

  Serial.print("runMillis = "); Serial.print(runMillis);
  Serial.print(" | |AccX= "); Serial.print(AccX);
  Serial.print(" | | AccY= "); Serial.print(AccY);
  Serial.print(" | | AccZ= "); Serial.print(AccZ);
  Serial.print(" | | GyroX= "); Serial.print(GyroX);
  Serial.print(" | | GyroY= "); Serial.print(GyroY);
  Serial.print(" | | GyroZ= "); Serial.println(GyroZ);
  Serial.print('\n');

  lcd.clear();
  lcd.print("Steps: ");
  lcd.print(counter);

  int a = 6000;
  int b = 14000;
  if((GyroX >= a) && (AccZ >= b))
  {
    counter++;
  }
  else if((GyroX <= -a) && (AccZ <= -b))
  {
    counter++;
  }
  else
  {
    
  }
  Serial.print("Counter = "); Serial.print(counter);


  myfile = SD.open("log.txt", FILE_WRITE);
  if (myfile)
  {
    myfile.print(AccX);
    myfile.print("\t");
    myfile.print(AccY);
    myfile.print("\t");
    myfile.print(AccZ);
    myfile.print("\t");
    myfile.print(GyroX);
    myfile.print("\t");
    myfile.print(GyroY);
    myfile.print("\t");
    myfile.print(GyroZ);
    myfile.print("\t");
    myfile.print(counter);
    myfile.print("\t");
    runMillis = millis();
    myfile.println(runMillis);
  }
    myfile.close();

  delay(300);
}
