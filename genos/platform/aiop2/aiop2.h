#ifndef G_AIOP2
	#define G_AIOP2
	
	
	#include "Arduino.h"
	
	static void aiop2_init()
	{
pinMode(13,1);
pinMode(30,1);
pinMode(31,1);
Serial.begin(9600);
	};
	
	static void aiop2_tmr1_int_on(){
		TIMSK1 |= _BV(TOIE1);
		};
	
#endif