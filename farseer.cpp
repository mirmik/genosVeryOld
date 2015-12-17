



#include "genos/debug/farseer.h"
//#include "genos/syscontext/syscontext.h"

//list_head farseer_list;

void farseer_all_see()
{
	farseer_variable* fvar;
	debug_print("***FARSEER_UTILITY***\n");
	list_for_each_entry(fvar, &farseer_list, list)
	{
			debug_print(fvar->func);
			debug_putchar(':');
			debug_print(fvar->var.type());
			debug_putchar(':');
			debug_print(fvar->name);						
			debug_print(" = ");
			debug_print(fvar->var.to_string().to_cstr());
			debug_putchar('\n');
	};
	
};