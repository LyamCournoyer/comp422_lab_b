byte INPUT_PIN = 6;
byte OUTPUT_PIN = 13;
void setup() { 
  // put your setup code here, to run once:
  pinMode(OUTPUT_PIN, OUTPUT);  
  pinMode(INPUT_PIN, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  if (digitalRead(INPUT_PIN)){
    digitalWrite(OUTPUT_PIN, LOW);
  }
  else{
    digitalWrite(OUTPUT_PIN, HIGH);
  }
}
