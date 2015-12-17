
#include "genos/debug/debug.h"
#include "genos/schedproc/scheduler_base.h"
#include <genos/base_struct/list.h>
#include "genos/base_struct/bits.h"

static process_base* __current_proc = nullptr;

process_base* current_process() {return __current_proc;};
void current_process(process_base* proc){__current_proc = proc;};


scheduler_base* scheduler_base::__sched = nullptr;

list_head process_list;
list_head running_list;
list_head waiting_list;
list_head zombie_list;
list_head stop_list;


	
	




scheduler_base& scheduler() {return *scheduler_base::__sched;};
void scheduler(scheduler_base& _sched) {scheduler_base::__sched = &_sched;};


bool scheduler_base::ready(){
	return (bits_mask_internal_or(sched_flags, BLOCK_MASK) || process_operation)  ? false : true; 
};


void subst_scheduler_base::block_sched()
{
	sched_flags |= SCHED_BLOCK;
};

void subst_scheduler_base::unblock_sched()
{
	sched_flags &= ~SCHED_BLOCK;
};


void scheduler_base::block()
{
	sched_flags |= USER_BLOCK;
};

void scheduler_base::unblock()
{
	sched_flags &= ~USER_BLOCK;
};


void thread_constructor::construct_thread(size_t size_of_stack) 			
{														
	stack = construct_dynamic_stack(size_of_stack);		//Конструирует стек нужного размера
	thr = new thread;									//Конструирует нить.
	set_stack_thread(thr, stack->top());				//Передаёт стек нити.
};

void thread_constructor::construct_current_thread(size_t stack_top) 			
{		
	stack = 0;
	thr = new thread;
	init_current_thread(thr, stack_top);
	thr_flags = THR_NODELETED;
};


void thread_constructor::destroy_thread()									
{														
	if ((thr_flags & THR_NODELETED)!=THR_NODELETED){				//Если явно не запрещено,					
	free(stack);};										//то уничтожает стек.
	delete thr;											//И, в любом случае, уничтожает нить
};












