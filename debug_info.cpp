

	#include "genos/base_struct/list.h"
	#include "genos/debug/debug.h"
	
	void debug_info(list_head* lst)
	{
		debug_printhex_ptr(lst->prev); dpc(':');
		debug_printhex_ptr(lst); dpc(':');
		debug_printhex_ptr(lst->next); dpc(':');
		debug_printhex_ptr(lst->prev->next); dpc(':');
		debug_printhex_ptr(lst->next->prev); dpc(':');
		
		};