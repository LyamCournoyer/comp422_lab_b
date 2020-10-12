#define pin A0
void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode (pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t value = analogRead (pin);
  uint16_t range = 4800/(analogRead(pin)-20);

//  get_gp2d12 (value);
  Serial.println (value);
  Serial.print (range);
  Serial.println (" mm");
  Serial.println ();
  delay (1000);
}

uint16_t get_gp2d12 (uint16_t value) 
{
  if (value < 10) value = 10;
  return ((67870.0 / (value - 3.0)) - 40.0);
}
