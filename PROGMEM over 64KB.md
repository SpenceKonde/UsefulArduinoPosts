per https://forum.arduino.cc/index.php?topic=387506.0 post 10. 

#define PROGMEM_LATE __attribute__ (( __section__(".fini1") ))
const PROGMEM_LATE uint16_t data1[] = {big array};

