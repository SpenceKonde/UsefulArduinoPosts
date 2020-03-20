// call in setup, passing frequency as argument, second argument should be 0 for normal fast pwm (single ramp), or 1 for phase correct, 2 for phase and frequency correct.
```
void initPWM(unsigned long freq,byte rampmode) {
	//calculate TOP
	unsigned long clockspercycle=(F_CPU/freq);
	if (rampmode) { //dual slope mode requested
		clockspercycle>>1;
	}
	byte presc=1; //this is the value to be written to the CS bits, NOT the actual prescaler
	while (clockspercycle>65536) { //do we need to prescale? 
		presc++; //increase prescaling
		clockspercycle=clockspercycle>>(presc>3?2:3); //divide required top by 8 or 4
		//no test needed for whether we've exhausted available prescalers, because 20,000,000/1024 will fit in 16-bits, and that's the highest rated speed for classic AVRs
	}
	// reset registers
	TCCR5B=0; 
	TCCR5A=0; 
	byte wgm=(rampmode?(rampmode==1?10:8):14); //determine desired WGM
	ICR5=clockspercycle-1;
	//clear these for good measure
	OCR5A=0;
	OCR5B=0;
	OCR5C=0;
	TCCR5A=0x03&wgm; //set low bits of WGM 
	TCCR5B=((wgm<<3)&0x18)|presc; //set rest of WGM, prescaler and start timer
}
//8-bit resolution, like analogWrite()
void setPWMDutyCycle8Bit(byte pin,byte dutycycle) {
	unsigned int ocrval=map(dutycycle,0,255,0,ICR5)
	if (!(pin==44||pin==45||pin==46)) { //if we call on a pin that isn't on this timer, return immediately.
		return; 
	}
	switch (pin)
	{
		case 46:
			OCR5A=ocrval;
			TCCR5A|=0x80; //COMA=2 non-inverting pwm
			break;
		case 45:
			OCR5B=ocrval;
			TCCR5A|=0x20; //COMA=2 non-inverting pwm
			break;
		case 44:
			OCR5B=ocrval;
			TCCR5A|=0x08; //COMA=2 non-inverting pwm
			break;
	}
	pinMode(pin,OUTPUT);
}

void disablePWMOutput(pin) {
	if (!(pin==44||pin==45||pin==46)) { //if we call on a pin that isn't on this timer, return immediately.
		return; 
	}
	switch (pin)
	{
		case 46:
			TCCR5A&=0x3F; //COMA=0 off
			break;
		case 45:
			TCCR5A&=0xCF; //COMA=0 off
			break;
		case 44:
			TCCR5A&=0xF3; //COMA=0 off
			break;
	}
	pinMode(pin,INPUT); //This may not be the ideal behavior for your use case - possibly digitalWrite'ing it LOW would be better.
}

/* 
// uncomment and fill in MAX to get a high-res version where duty cycle expressed as 0~MAX
void setDutyCycleHiRes(byte pin,unsigned int dutycycle) {
	unsigned int ocrval=map(dutycycle,0,MAX,0,ICR5)
	if (!(pin==44||pin==45||pin==46)) { //if we call on a pin that isn't on this timer, return immediately.
		return; 
	}
	switch (pin)
	{
		case 46:
			OCR5A=ocrval;
			TCCR5A|=0x80; //COMA=2 non-inverting pwm
			break;
		case 45:
			OCR5B=ocrval;
			TCCR5B|=0x80; //COMA=2 non-inverting pwm
			break;
		case 44:
			OCR5C=ocrval;
			TCCR5C|=0x80; //COMA=2 non-inverting pwm
			break;
	}
	pinMode(pin,OUTPUT);
}
*/
```
