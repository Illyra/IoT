unsigned long runMillis;
const int currentPin = A0;
const int voltPin = A1;
int resistance = 100;
float vout = 0.0;
float vin = 0.0;
float R1 = 30000.0; //onboard resistor 1 value
float R2 = 7500.0; //onboard resistor 2 value
int svalue = 0;
float sensitivity = 0.1;
int adcValue = 0;
float offsetVoltage = 2.5;
double adcVoltage = 0;
double currentValue = 0;
double currentValue2 = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(currentPin, INPUT);
  pinMode (voltPin, INPUT);
}

void loop() 
{
  adcValue = analogRead(currentPin);
  adcVoltage = (adcValue / 1024.0) * 5;
  currentValue = ((adcVoltage - offsetVoltage) / sensitivity);

  svalue = analogRead(voltPin); //reads the value from sensor
  vout = (svalue * 5.0) / 1024.0;
  vin = vout / (R2 / (R1 + R2));
  currentValue2 = vin / resistance;

  Serial.print(currentValue, 3);
  Serial.print("\t");
  Serial.print(vin);
  Serial.print("\t");
  Serial.print(currentValue2, 3);
  Serial.print("\t");
  runMillis = millis();
  Serial.println(runMillis);

  delay(1000);
}
