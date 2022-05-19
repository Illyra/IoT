#include <arduinoFFT.h>
arduinoFFT FFT = arduinoFFT();


unsigned long runMillis;
int analogInput_vol = A0;
float vout = 0.0;
float vin = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int svalue = 0;

const int SAMPLING_FREQUENCY = 100;
const int windowsize = 128;
double vReal[windowsize];
double vImag[windowsize];

void setup() 
{
  Serial.begin(9600);
  pinMode(analogInput_vol, INPUT);
}

void loop() 
{
  for(int i = 0; i < windowsize; i++)
  {
    svalue = analogRead(analogInput_vol);
    vout = (svalue * 5.0) / 1024.0;
    vin = vout / (R2 / (R1 + R2));

    vReal[i] = float(int(vin *100)) / 100;
    vImag[i] = 0;

    delay(1000 / SAMPLING_FREQUENCY);
  }

  FFT.Compute(vReal, vImag, windowsize, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, windowsize);
  double peak = FFT.MajorPeak(vReal, windowsize, SAMPLING_FREQUENCY);

  Serial.print(peak);
  Serial.print("\t");
  runMillis = millis();
  Serial.println(runMillis);

}
