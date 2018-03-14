### Basic PROGMEM array

```
const byte pgmArray[] PROGMEM={1,2,3,4,5}; 

byte valueFromPROGMEM=pgm_read_byte_near(&pgmArray[2]); //remember the &

```


### Array of PROGMEM strings

Putting a bunch of strings into PROGMEM is a bit awkward - there's no one-line way to make the array - but works the same way. Almost all the functions to work with c strings have a _P (ex, snprintf_P() ) version that takes a pointer to PROGMEM string instead of a c string in RAM. 

```
const char mode0L0[] PROGMEM="  RED  ";
const char mode0L1[] PROGMEM=" GREEN ";
const char mode0L2[] PROGMEM="  BLUE ";
const char mode1L3[] PROGMEM=" WHITE ";


const char * const modesL[][8] ={
  {mode0L0,mode0L1,mode0L2},
  {mode0L0,mode0L1,mode0L2,mode1L3}
  
};
```

To print, we can take advantage of __FlashStringHelper (which is used internally to make the F() macro work) to print these strings straight from PROGMEM: 


```

Serial.println(reinterpret_cast<const __FlashStringHelper *>(modesL[1][3])); //prints " WHITE "

#define FLASH_STRING(flashptr) (reinterpret_cast<const __FlashStringHelper *>(flashptr))

Serial.println(FLASH_STRING(modesL[1][3])); //same thing, but much cleaner using above macro

```



### PROGMEM array of PROGMEM strings

The above keeps the array of pointers to the PROGMEM strings in RAM. This still wastes 2 bytes of RAM per entry, though. We can keep the pointers in PROGMEM too to save that memory - but then we need to access them like something that's in progmem:

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

Printing:

```

Serial.println(reinterpret_cast<const __FlashStringHelper *>(pgm_read_word_near(&modesL[1][3]))); //prints " WHITE "

#define FLASH_STRING(flashptr) (reinterpret_cast<const __FlashStringHelper *>(pgm_read_word_near(&flashptr)))

Serial.println(FLASH_STRING(modesL[1][3])); //same thing, but much cleaner using above macro

```
