

#include "genos/base_struct/list.h"
//#include "genos/time/timeserv.h"
#include "genos/time/basic_timer.h"
#include "genos/debug/debug.h"

void debug_info(list_head* lst)
{
	debug_printhex_ptr(lst->prev); debug_putchar(':');
	debug_printhex_ptr(lst); debug_putchar(':');
	debug_printhex_ptr(lst->next); debug_putchar(':');
	debug_printhex_ptr(lst->prev->next); debug_putchar(':');
	debug_printhex_ptr(lst->next->prev); debug_putchar(':');
	
};

/*
void debug_info(genos::timer_service* tmrsrv)
{
	for (auto rec: tmrsrv->lst)
	{
		debug_printhex_uint8(rec.trait);dpc(':');
		debug_printhex_uint64(rec.info);dpc(':');
		debug_printhex_uint32(rec.tmr.finish());dpc(':');dln;
	};
};*/




void  list_check(list_head* list, int m =20)
{
	debug_print("list_check:\n");
	int n;
	list_head* tmp = list;
	if (list_empty(list)) {debug_print("list empty");return;}; 
	for (n=0;n < m; n++)
	{
		if ((size_t)list < 0x50) {debug_panic("list_next_zero\n");}; 
		if ((size_t)list > RAMEND - 0x50) {debug_panic("list_next_RAMEND\n");};
		debug_printhex_ptr(list->prev);debug_putchar(':');
		debug_printhex_ptr(list);debug_putchar(':');
		debug_printhex_ptr(list->next);debug_putchar(':');
		debug_putchar('\n');
		list = list -> next;
		if (list == tmp) {debug_print("list_next_correct\n");goto stage2;}; 		
	};
	debug_panic("list_next_count is over\n");
	stage2:
	list = tmp;
	for (n=0;n < m; n++)
	{
		if ((size_t)list < 0x50) {debug_panic("list_prev_zero\n");};
		if ((size_t)list > RAMEND - 0x50) {debug_panic("list_prev_RAMEND\n");};
		debug_printhex_ptr(list->prev);debug_putchar(':');
		debug_printhex_ptr(list);debug_putchar(':');
		debug_printhex_ptr(list->next);debug_putchar(':');
		debug_putchar('\n');
		list = list -> prev;
		if (list == tmp) {debug_print("list_prev_correct\n");goto stage3;}; 
	};
	debug_panic("list_prev_count is over\n"); 
	stage3:;
	return;
};