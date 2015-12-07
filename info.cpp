


#include <genos/iostream/iostream.h>
#include "genos/info.h"



genos::ostream& operator<< (genos::ostream& o, thread& thr){
	o << genos::alldigits <<
	genos::setw(0) << genos::hex << genos::noshowbase << &thr << ':' 
	<< thr.stack_pointer << ':' << thr.stack_top;
	
	o << genos::reset;
	return o;
};

/*ostream& operator<< (ostream& o, process& proc){
	o << alldigits <<
	setw(0) << hex << noshowbase 
	<< &proc << ':' << proc.state ;
	o << reset;
	return o;
};*/


/*
	void os_print_proclist(ostream& os)
	{
	os << alldigits <<
	setw(0) << hex << noshowbase;
	
	process* proc;
	list_for_each_entry(proc, &process_list, prclist)
	{
	os << proc << endl;
	};
	
	};*/
	void debug_info(thread& thr){
		debug_printhex_ptr(&thr); dpc(':');
		debug_printhex_uint16(thr.stack_pointer);dpc(':');
		debug_printhex_uint16(thr.stack_top);
	};
	
	void debug_info(thread_constructor& tc)
	{
		debug_printhex_uint16((uint16_t)tc.thr); 		debug_putchar(':');
		debug_printhex_uint16(tc.thr->stack_pointer);	debug_putchar(':');
		debug_printhex_uint16(tc.thr->stack_top);		debug_putchar(':');
		debug_printhex_uint16((uint16_t)tc.stack);			
	};
	
	void debug_info(maScheduler::thread_manager& tm)
	{
		debug_info((thread_constructor&)tm);		
	};
	
	void debug_info(maScheduler& ma , int i)
	{
		switch (i)
		{
			case 0:
			for(int i=0;i<THREAD_NUM;i++)
			{debug_info((maScheduler::thread_manager&)ma.thr_array[i]);
			debug_putchar('\n');}
			break;
			case 1:
			maScheduler::atom_process* proc;
			list_for_each_entry(proc, &process_list, prc_list)
			{
				debug_printhex_ptr(proc);					debug_putchar(':');
				debug_printhex_ptr((void*)proc->execobj);	debug_putchar(':');
				debug_printhex_uint8(proc->prctype);		debug_putchar(':');
				debug_printhex_uint16(proc->param1);		debug_putchar(':');
				debug_printhex_uint16(proc->param2);		debug_putchar(':');
				debug_printhex_uint16(proc->priority);		debug_putchar(':');
			debug_print(proc->name);						debug_putchar('\n');};
			break;
		};
		
		
	};	