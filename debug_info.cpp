

	#include "genos/base_struct/list.h"
	#include "genos/time/timerserv.h"
	#include "genos/time/basic_timer.h"
	#include "genos/debug/debug.h"
	
	void debug_info(list_head* lst)
	{
		debug_printhex_ptr(lst->prev); dpc(':');
		debug_printhex_ptr(lst); dpc(':');
		debug_printhex_ptr(lst->next); dpc(':');
		debug_printhex_ptr(lst->prev->next); dpc(':');
		debug_printhex_ptr(lst->next->prev); dpc(':');
		
		};
		
		
	void debug_info(genos::timer_service* tmrsrv)
	{
		for (auto rec: tmrsrv->lst)
		{
		debug_printhex_uint8(rec.trait);dpc(':');
		debug_printhex_uint64(rec.info);dpc(':');
		debug_printhex_uint32(rec.tmr.finish());dpc(':');dln;
		};
		};
		
		
		
		
			void  list_check(list_head* list, int m =20)
	{
		dpr("list_check:\n");
		int n;
		list_head* tmp = list;
		for (n=0;n < m; n++)
		{
			if ((size_t)list < 0x50) {debug_panic("list_next_zero\n");}; 
			if ((size_t)list > RAMEND - 0x50) {debug_panic("list_next_RAMEND\n");};
			debug_printhex_ptr(list->prev);dpc(':');
			debug_printhex_ptr(list);dpc(':');
			debug_printhex_ptr(list->next);dpc(':');
			dln;
			list = list -> next;
			if (list == tmp) {dpr("list_next_correct\n");goto stage2;}; 		
		};
		debug_panic("list_next_count is over\n");
		stage2:
		list = tmp;
		for (n=0;n < m; n++)
		{
			if ((size_t)list < 0x50) {debug_panic("list_prev_zero\n");};
			if ((size_t)list > RAMEND - 0x50) {debug_panic("list_prev_RAMEND\n");};
			debug_printhex_ptr(list->prev);dpc(':');
			debug_printhex_ptr(list);dpc(':');
			debug_printhex_ptr(list->next);dpc(':');
			dln;
			list = list -> prev;
			if (list == tmp) {dpr("list_prev_correct\n");goto stage3;}; 
		};
		debug_panic("list_prev_count is over\n"); 
		stage3:;
		return;
	};