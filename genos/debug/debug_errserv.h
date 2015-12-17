#ifndef GENOS_DEBUG_ERRSERV
	#define GENOS_DEBUG_ERRSERV
	
	#include "genos/platform/debug.h"
	
	static void debug_halt() __attribute__((always_inline));	
	static void  debug_halt() 
	{
		NOTEMP_ATOMIC();
		debug_print("system halt");
		while(1);
	};
	
	
	
	static void debug_panic(char* str) __attribute__((always_inline));		
	static void debug_panic(char* str)
	{
		uint8_t temp;
		NOTEMP_ATOMIC(); 
		debug_print_init(); 
		debug_print(str); 
		debug_putchar('\n');
		debug_print("Kernel panic! "); 
		debug_halt();	
	};
	
#endif