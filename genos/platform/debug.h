
#ifndef GENOS_PLATFORM_DEBUG_H
	#define GENOS_PLATFORM_DEBUG_H
	
	#include "genos/platform/interrupt.h"
	
	
	#ifdef ARDUINO
		
		//#ifndef cli()
			#include "avr/interrupt.h"
	//#endif
				
		#define SERIAL_8N1 0x06
		#include <avr/io.h>
		static void debug_print_init() __attribute__((always_inline));
		static void debug_print_init()
		{
			
			UCSR0A = 0;
			uint16_t baud_setting = (F_CPU / 8 / 9600 - 1) / 2;
			
			// assign the baud_setting, a.k.a. ubrr (USART Baud Rate Register)
			UBRR0H = baud_setting >> 8;
			UBRR0L = baud_setting;
			
			uint8_t config = SERIAL_8N1;
			//set the data bits, parity, and stop bits
			#if defined(__AVR_ATmega8__)
				config |= 0x80; // select UCSRC register (shared with UBRRH)
			#endif
			UCSR0C = config;
			
			UCSR0B|= _BV(RXEN0);
			UCSR0B|= _BV(TXEN0);
			UCSR0B|= _BV(RXCIE0);
			UCSR0B&= ~_BV(UDRIE0);
		};
		
		static void debug_putchar(char c) __attribute__((always_inline));
		static void debug_putchar(char c)
		{
			static uint8_t debug_print_inited = 0;		
			ATOMIC(temp);
			while ((UCSR0A & (1 << UDRE0)) == 0) {};  UDR0=c; 
			DEATOMIC(temp);
		};
		
	#endif
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
#endif


