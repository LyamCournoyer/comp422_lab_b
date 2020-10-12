#include <avr/io.h>
#define InputLedDirection DDRD
#define InputLedRegister PORTD
#define InputPinRegister PIND
#define InputLedBit (1 << 6)


#define OutputLedDirection DDRB
#define OutputLedRegister PORTB
#define OutputLedBit (1 << 5)

void setup() {
  // put your setup code here, to run once:
  OutputLedDirection |= OutputLedBit;
  InputLedDirection &= ~InputLedBit;
  InputLedRegister |= InputLedBit;

}

void loop() {
  if(!(InputPinRegister & InputLedBit)){
    OutputLedRegister |= OutputLedBit;
  }
  else{
    OutputLedRegister &= ~OutputLedBit;
  }

}
