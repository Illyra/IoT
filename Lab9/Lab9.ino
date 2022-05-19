int soundPin = 4;
int LEDPin1 = 2;
int LEDPin2 = 13;
int LEDstate;
int LEDstate2;


void setup() 
{
  pinMode(LEDPin1, OUTPUT);
  pinMode(LEDPin2, OUTPUT);
  digitalWrite(LEDPin1,LOW);
  digitalWrite(LEDPin2,LOW);
  LEDstate = 0;
  LEDstate2 = 0;
}

void loop() 
{
  int tmp = digitalRead(soundPin);
  Serial.println(tmp);
  //1
  if(!tmp)
  {
    if (LEDstate == 0)
    {
      digitalWrite(LEDPin1, HIGH);
      LEDstate = 1;
    }
    else 
    {
      digitalWrite(LEDPin1, LOW);
      LEDstate = 0;
    }
    delay(1000);
  }
  else
  {
    delay(1);
  }
  //2
  if(!tmp)
  {
    if (LEDstate2 == 0)
    {
      digitalWrite(LEDPin2, HIGH);
      LEDstate2 = 1;
    }
    else 
    {
      digitalWrite(LEDPin2, LOW);
      LEDstate2 = 0;
    }
    delay(100);
  }
//  else
//  {
//    delay(1);
//  }
}
