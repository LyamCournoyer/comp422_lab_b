#include <avr/io.h>

#define OutputLedDirection DDRD
#define OutputLedRegister PORTD
#define OutputLedBit (1 << 5)

const int maxOnMillis = 10;
const int onMillisChangeRate = 3;
const int delayBeforeBrightnessChange = 2000; 

int minOffMillis = 10;
int currentOnMillis = maxOnMillis;

 unsigned long previousMillis = 0; 

void setup() {
  Serial.begin (9600);
   OutputLedDirection |= OutputLedBit;
  turnOnRegisterBit(OutputLedDirection, OutputLedBit);
  turnOnRegisterBit(OutputLedRegister, OutputLedBit);

}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= delayBeforeBrightnessChange) {    
    previousMillis = currentMillis;
    currentOnMillis = (currentOnMillis + onMillisChangeRate)% maxOnMillis;
    Serial.print("Current brightness ");
    Serial.println(currentOnMillis);
    
  }
  turnOnRegisterBit(OutputLedRegister, OutputLedBit);
  delay(currentOnMillis);
  turnOffRegisterBit(OutputLedRegister, OutputLedBit);
  delay(minOffMillis);
}

void turnOnRegisterBit(int ledRegister, int bitPos){
  OutputLedRegister |= OutputLedBit;
//  ledRegister |= (1 << bitPos);
}

void turnOffRegisterBit(int ledRegister, int bitPos){
   OutputLedRegister &= ~OutputLedBit;
//  ledRegister &= ~(1 << bitPos);
}

int getNewBrightness(){
  
}
