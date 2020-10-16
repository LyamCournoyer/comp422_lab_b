#define ledPin 13
#include <avr/io.h>
#include <avr/interrupt.h>

#define InputLedDirection DDRD
#define InputLedRegister PORTD
#define InputPinRegister PIND
#define InputLedBit (1 << 2)

void setup(){
  cli();
  Serial.begin (9600);
  pinMode(ledPin, OUTPUT);
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
  OCR1A = 39062;            // compare match register 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12);   // CTC mode
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  TCCR1B |= (1 << CS12) + (1 << CS10);    // 256 prescaler 
}

ISR(TIMER1_COMPA_vect) {
  cli();
  Serial.println("timer interupt");
  digitalWrite(ledPin, LOW);   // toggle LED pin
  TCCR1A = 0;
  TCCR1B = 0;
  sei();
}


ISR(INT0_vect){  
  cli();
  Serial.println("INT0 interupt");
  Serial.println(digitalRead(2));
  if (digitalRead(2) == LOW){
    
    digitalWrite(ledPin, HIGH);
    myDelay();
  }
  sei();
  
}

void loop()

{

  while(1){};

}
