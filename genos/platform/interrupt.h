		
		#ifndef GENOS_PLATFORM_INTERRUPT__H
		#define GENOS_PLATFORM_INTERRUPT__H
		
		#ifdef ARDUINO
		#include "avr/io.h"
		#include "avr/interrupt.h"
		#define ATOMIC(temp) uint8_t temp = SREG; cli();
		#define DEATOMIC(temp)  SREG = temp;
		
		#define NOTEMP_ATOMIC() cli()
		#define NOTEMP_DEATOMIC() sei()
		#endif
		
		
		
		
		
		
		
		
		#endif