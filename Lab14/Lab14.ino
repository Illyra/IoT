int transistorpin = 7;
int freq = 10;
int halfcycle = 1000 / freq / 2;

void setup() 
{
  Serial.begin(9600);
  pinMode(transistorpin, OUTPUT);
  digitalWrite(transistorpin, LOW);
}

void loop() 
{
  digitalWrite(transistorpin, HIGH);
  delay(halfcycle);
  digitalWrite(transistorpin, LOW);
  delay(halfcycle);

}
