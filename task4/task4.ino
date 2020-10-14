#include <avr/io.h>

#define OutputLedDirection DDRD
#define OutputLedRegister PORTD
#define OutputLedBit (1 << 5);

const int MAX_ON_MILLIS = 10;
const int MIN_OFF_MILLIS = 10;

const int ON_MILLIS_CHANGE_RATE = 3;
const int BRIGHTNESS_CHANGE_DELAY = 2000; 


int currentOnMillis = MAX_ON_MILLIS;
unsigned long previousMillis = 0; 

void setup() {
   Serial.begin (9600);
   OutputLedDirection |= OutputLedBit;  
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= BRIGHTNESS_CHANGE_DELAY) {    
    previousMillis = currentMillis;
    currentOnMillis = getNewBrightness(currentOnMillis);
    Serial.print("Current brightness ");
    Serial.println(currentOnMillis);
    
  }
  turnOnRegisterBit();
  delay(currentOnMillis);
  turnOffRegisterBit();
  delay(MIN_OFF_MILLIS);
}

void turnOnRegisterBit(){
  OutputLedRegister |= OutputLedBit;
}

void turnOffRegisterBit(){
   OutputLedRegister &= ~OutputLedBit;
}

int getNewBrightness(int currentOnMillis){
  return (currentOnMillis + ON_MILLIS_CHANGE_RATE)% MAX_ON_MILLIS;
}
