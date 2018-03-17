### Use a rotary encoder (like those ubiquitous knobs from ebay)
Rotary encoders are widely used for knobs on control panels. The most common kind gives 4 transitions per detent - this code (shamelessly stolen and adapted as noted below) demonstrates doing this in a way that works. 

In this case the maximum value for the setting is stored in a byte called maxValueLeft and maxValueRight (for the two rotary encoders). 

currentValueLeft and currentValueRight are declared volatile byte. 

The encoders are on pins A0~A3 (PC0~PC3) on an atmega328p. Two LUT's are provided - they go in opposite directions; if it's going the wrong direction, comment out the one you're using and uncomment the other one. 

```
//called from setup
void setupPCINT() {
  PCMSK1 = 0x0F;
  PCICR = 2;
}

// ISR based on: https://www.circuitsathome.com/mcu/rotary-encoder-interrupt-service-routine-for-avr-micros/
// by Oleg Mazurov
ISR(PCINT1_vect)
{
  static uint8_t old_ABl = 3;  //lookup table index
  static int8_t enclval = 0;   //encoder value
  static uint8_t old_ABr = 3;  //lookup table index
  static int8_t encrval = 0;   //encoder value
  //static const int8_t enc_states [] PROGMEM = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};  //encoder lookup table
  static const int8_t enc_states [] PROGMEM = {0, 1, -1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 0, -1, 1, 0}; // reversed encoder table
  /**/
  old_ABl <<= 2; //remember previous state
  old_ABr <<= 2; //remember previous state
  old_ABl |= ( PINC & 0x03 );
  old_ABr |= (( PINC & 0x0C ) >> 2);
  enclval += pgm_read_byte(&(enc_states[( old_ABl & 0x0f )]));
  encrval += pgm_read_byte(&(enc_states[( old_ABr & 0x0f )]));
  /* post "Navigation forward/reverse" event */
  if ( enclval > 3 ) { //four steps forward
    currentValueLeft++;
    if (currentValueLeft > maxValueLeft)currentValueLeft = 0;
    enclval = 0;
  }
  else if ( enclval < -3 ) { //four steps backwards
    currentValueLeft--;
    if (currentValueLeft == 255)currentValueLeft = maxValueLeft;
    enclval = 0;
  }
  if ( encrval > 3 ) { //four steps forward
    currentValueRight++;
    if (currentValueRight > maxValueRight) currentValueRight = 0;
    encrval = 0;
  }
  else if ( encrval < -3 ) { //four steps backwards
    currentValueRight--;
    if (currentValueRight == 255)currentValueRight = maxValueRight;
    encrval = 0;
  }
}
```
