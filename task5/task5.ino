
#include <avr/io.h>
#include <avr/interrupt.h>

#define InputLedDirection DDRD
#define InputLedRegister PORTD
#define InputPinRegister PIND
#define InputLedBit (1 << 2)

#define OutputLedDirection DDRB
#define OutputLedRegister PORTB
#define OutputLedBit (1 << 5)

#define TimerCompareVal 39062; //2.5 sec

void setup(){
  cli();
  Serial.begin (9600);
  OutputLedDirection |= OutputLedBit;
  
  InputLedDirection &= ~InputLedBit;
  InputLedRegister |= InputLedBit;
  EICRA |= (1 << ISC01);
  EIMSK |= (1 << INT0);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
  sei();
  Serial.println("start");
 
}

void myDelay(void){
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = TimerCompareVal;
  TCCR1B |= (1 << WGM12);
  TIMSK1 |= (1 << OCIE1A);
  TCCR1B |= (1 << CS12) + (1 << CS10);
}

ISR(TIMER1_COMPA_vect) {
  cli();
  Serial.println("timer interupt");
  OutputLedRegister &= ~OutputLedBit;
  TCCR1A = 0;
  TCCR1B = 0;
  sei();
}


ISR(INT0_vect){  
  cli();
  Serial.println("INT0 interupt");
  Serial.println(digitalRead(2)); 
  Serial.println(!(InputPinRegister & InputLedBit)); 
  if (!(InputPinRegister & InputLedBit)){   
    OutputLedRegister |= OutputLedBit;
    myDelay();
  }
  sei();
  
}

void loop()

{
  while(1){};
}
