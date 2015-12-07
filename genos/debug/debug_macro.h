

#ifndef GENOS_DEBUG_MACRO
	#define GENOS_DEBUG_MACRO
	


//#include <genos/debug/errserv.h>
#include <genos/debug/debug_print.h>	


//Макросы debug_print
#define dpr_tab() {debug_putchar('\t');}
#define dwr(a,b) {debug_write(a,b);}
#define dpr_hex(a) debug_printhex_uint32((int32_t)a)
#define printd(a) {debug_print(a);}
#define dpr_str(a) {debug_print(a);}
#define dpr(a) {debug_print(a);}
#define dpc(a) {debug_putchar(a);}
#define dln debug_write("\r\n",2);
#define dtb debug_putchar('\t');




//Макросы debug_errserv

#define dcntstp(dbgint, a) dbgint++; if (dbgint==a) {debug_stop();};
#define debug_panic(a) {cli(); debug_print_init(); debug_print(a); dln;  \
debug_print("Kernel panic!"); debug_stop();}

#define debug_stop() {cli();asm("1: rjmp 1b");} 
#define dstp debug_stop()
#define dprcond(a, str) {if (a) debug_print(str);}
#define dstpcond(a) {if (a) debug_stop();}
#define dcond(a) if (a) 













#endif