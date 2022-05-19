unsigned long runMillis;
int analogInput_vol = A0;
float vout = 0.0;
float vin = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int svalue = 0;
int ledpin = 13;
int voltthresh = 2;

void setup()
{
  Serial.begin(9600);
  pinMode(analogInput_vol, INPUT);
  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, LOW);
}

void loop() 
{
  svalue = analogRead(analogInput_vol);
  vout = (svalue * 5.0) / 1024.0;
  vin = vout / (R2 /(R1 + R2));

  Serial.println(vin);

  if(vin > voltthresh)
  {
    digitalWrite(ledpin, HIGH);
  }
  else
  {
    digitalWrite(ledpin, LOW);
  }
  delay(100);

}
