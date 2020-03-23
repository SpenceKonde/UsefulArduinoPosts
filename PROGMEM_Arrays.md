### PROGMEM is not needed on megaavr
This page is not relevant if you are using a megaavr part. The megaavr product line currently includes the TinyAVR 0-series and 1-series parts (supported on Arduino by my megaTinyCore https://github.com/SoenceKonde/megaTinyCore ) and the MegaAVR 0-series (used in the official Uno WiFi Rev. 2, and supported for the whole product line via https://github.com/MCUdude/MegaCoreX ). Parts not based on the AVR architecture may use different methods to mark constants as belonging on flash rather than in RAM. The unified address space is one of the most compelling advantages to using the megaavr product line.

In any event, the megaavr parts have a unified address space, so no special instruction is required to read data that is stored on flash instead of in SRAM. Because of this, the compiler can automatically put all variables declared `const` into flash without an explicit `PROGMEM` declaration. You can still declare variables as `PROGMEM` - though there is no reduction ro memory usage if you do - but if you do this, you must still the `pgm_read_...` macros to read it. 

Behind the scenes, the flash starts at either 0x8000 (for tinies) or 0x4000 (for megas). If the variable was declared PROGMEM, the pointer be referenced to the start of the flash section. You can examine the addresses that the variables point to in order to demonstrate this - If you are curious about this, I recommend it..

### Basic PROGMEM array

```c++
const byte pgmArray[] PROGMEM={1,2,3,4,5}; 

byte valueFromPROGMEM=pgm_read_byte_near(&pgmArray[2]); //remember the &
```


### Array of PROGMEM strings

Putting a bunch of strings into PROGMEM is a bit awkward - there's no one-line way to make the array - but works the same way. Almost all the functions to work with c strings have a _P (ex, snprintf_P() ) version that takes a pointer to PROGMEM string instead of a c string in RAM. 

```c++
const char mode0L0[] PROGMEM="  RED  ";
const char mode0L1[] PROGMEM=" GREEN ";
const char mode0L2[] PROGMEM="  BLUE ";
const char mode1L3[] PROGMEM=" WHITE ";


const char * const modesL[][8] ={
  {mode0L0,mode0L1,mode0L2},
  {mode0L0,mode0L1,mode0L2,mode1L3}
  
};
```

To print, we can take advantage of `__FlashStringHelper` (which is used internally to make the F() macro work) to print these strings straight from PROGMEM:


```c++
Serial.println(reinterpret_cast<const __FlashStringHelper *>(modesL[1][3])); //prints " WHITE "

#define FLASH_STRING(flashptr) (reinterpret_cast<const __FlashStringHelper *>(flashptr))

Serial.println(FLASH_STRING(modesL[1][3])); //same thing, but much cleaner using above macro
```



### PROGMEM array of PROGMEM strings

The above keeps the array of pointers to the PROGMEM strings in RAM. This still wastes 2 bytes of RAM per entry, though. We can keep the pointers in PROGMEM too to save that memory - but then we need to access them like something that's in progmem:

```c++
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

```c++
Serial.println(reinterpret_cast<const __FlashStringHelper *>(pgm_read_word_near(&modesL[1][3]))); //prints " WHITE "

#define FLASH_STRING(flashptr) (reinterpret_cast<const __FlashStringHelper *>(pgm_read_word_near(&flashptr)))

Serial.println(FLASH_STRING(modesL[1][3])); //same thing, but much cleaner using above macro
```


## PROGMEM array of constant-length PROGMEM strings

The above method uses an array of pointers to strings. If all the strings have the same length, we can instead use a real array of strings, i.e. an array of NUL-terminated arrays of chars (a 2D array of chars). Then the intermediate string variables are not needed anymore, and we don't have to store the array of pointers:

```c++
const char modesL[][8] PROGMEM = {
    "  RED  ",
    " GREEN ",
    "  BLUE ",
    " WHITE "
};
```

Printing:

```c++
Serial.println(reinterpret_cast<const __FlashStringHelper *>(modesL[3])); //prints " WHITE ";

#define FLASH_STRING(flashptr) (reinterpret_cast<const __FlashStringHelper *>(flashptr))

Serial.println(FLASH_STRING(modesL[3])); //same thing, but much cleaner using above macro
```
