#include<avr/io.h>
#define OutputLedDirection DDRB
#define OutputLedRegister PORTB
#define OutputBit (1 << 5)

#define InputDirection DDRC
#define InputPort PORTC
#define InputPinRegister PINC
#define InputBit (1 << 2)
#define MinRange 670 //3.5 cm
#define MaxRange 685 //4.5cm
uint8_t low, high;
uint8_t analog_reference = DEFAULT;


void setup() {
  Serial.begin (9600);
  OutputLedDirection |= OutputBit;
  InputDirection  &= ~InputBit;

  DIDR0 |= InputBit;
  ADCSRA |= (1 << ADPS0) + (1 << ADPS1) + (1 << ADPS2);
  ADCSRA |= (1 << ADEN); //enable ADC
  ADCSRA |= (1 << ADSC); //enable ADC
  ADMUX |= (1 << 6);
  ADMUX |= (1 << MUX1); 
  ADCSRA = ADCSRA | (1 << ADSC);
  while(ADCSRA & (1 << ADSC));   
}

void loop() { 
  ADCSRA = ADCSRA | (1 << ADSC);
  while(ADCSRA & (1 << ADSC));   
  low  = ADCL;
  high = ADCH;
   uint16_t value =(high << 8) | low; // ADCL & (1 << 2);
   if ( value < MaxRange && value > MinRange){
      OutputLedRegister |= OutputBit;
   }
   else{
      OutputLedRegister &= ~OutputBit;
   }

  Serial.print (value);
  Serial.println ();
}
