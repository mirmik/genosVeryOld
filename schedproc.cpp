

#include "genos/schedproc/process_base.h"
#include "genos/schedproc/scheduler_base.h"

list_head process_list;

process_base* _current_process;

process_base* current_process(){return _current_process;};
void current_process(process_base* proc){_current_process = proc;};

scheduler_base* _current_scheduler;

scheduler_base* scheduler(){return _current_scheduler;};
	void scheduler(scheduler_base* _sched){_current_scheduler = _sched;};
	
	
	void debug_proclist_print()
	{
		list_head* it;
	list_for_each(it,&process_list) { debug_printhex_ptr(it); debug_putchar('\n'); };
		
	};