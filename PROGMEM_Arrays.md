### Basic PROGMEM array



### Array of PROGMEM strings




### PROGMEM array of PROGMEM strings

```
const char mode0L0[] PROGMEM="  RED  ";
const char mode0L1[] PROGMEM=" GREEN ";
const char mode0L2[] PROGMEM="  BLUE ";
const char mode1L3[] PROGMEM=" WHITE ";


const char * const modesL[][8] PROGMEM ={
  {mode0L0,mode0L1,mode0L2},
  {mode0L0,mode0L1,mode0L2,mode1L3}
  
};
```

To access:

```

Serial.println(reinterpret_cast<const __FlashStringHelper *>(pgm_read_word_near(&modesL[1][3]))); //prints " WHITE "

#define FLASH_STRING(flashptr) (reinterpret_cast<const __FlashStringHelper *>(pgm_read_word_near(&flashptr)))

Serial.println(FLASH_STRING(modesL[1][3])); //same thing, but much cleaner using above macro

```
