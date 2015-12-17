
#include "genos/debug/debug.h"
#include "genos/schedproc/gSched.h"
#include <genos/base_struct/list.h>
#include "genos/base_struct/bits.h"
#include "genos/debug/debug.h"
#include "genos/debug/farseer.h"

//static void idle(){while(1) scheduler().schedule();};

void gScheduler::init(){
	process* proc = new process;	
	proc->stack = 0;
	proc->thr = new thread;
	proc->thr_flags = THR_NODELETED;
	init_current_thread(proc->thr,RAMEND);
	process_init(proc);	
	current_process(proc);
	bits_clr(sched_flags, NO_INIT);
	current = stlst.running_list.next;
	//if (!fork(300)) idle();
};



gScheduler::process* gScheduler::fork(size_t stcksize){
	if (bits_mask_internal_or(sched_flags, NO_INIT)) {return (gScheduler::process*)-1;};
	block_sched();
	gScheduler::process* proc = new process;
	proc->construct_thread(stcksize);
	process_init(proc);	
	if (fork_thread(proc->thr))  
	{	
		unblock_sched(); 
		return proc;
	}
	else
	{
		return 0;
	};
	
};

void gScheduler::proc_delete(process* proc)
{
	proc->destroy_thread();
	process_unbind(proc);
	delete(proc);
};

void gScheduler::process_unbind(process* proc)
{
	ATOMIC(temp);
	list_del(&proc->prc_list);
	list_del(&proc->sts_list);
	delete(proc);
	DEATOMIC(temp);
};

void gScheduler::exit()
{
	process_set_zombie(current_process()); //Доктор сказал в морг
	cli(); 							//Имитируем вход в прерывание 	
	schedule();						//Вызываем планировщик.
	
	//При следующем проходе процесс будет уничтожен планировщиком.
}

void gScheduler::proc_go_wait()
{
	current = current->prev;
};


void gScheduler::schedule(){
	if (ready())
	{	
		process* proc;
		
		if (&stlst.running_list == stlst.running_list.next)			//Проверка на пустой список
		{debug_panic("No one running proc. HALT");};
			
			
			
			list_rotate_left(&stlst.running_list);	
			proc = list_entry(stlst.running_list.next, process, sts_list);//Указатель на процесс получить.
			
			//if (bits_mask_internal_or(proc->prc_flags, PROC_ZOMBIE)) 		//Если встретили зомби, добили его
			//{current=current->next; proc_delete(proc); goto strt;};
			
				current_process(proc);
				change_thread(proc->thr);
			
		};
		
	};
		
		
		
		
		
		
		//DEBUG
		
		void gScheduler::print_list(){
			
			list_head* ptr = stlst.running_list.next;
			debug_print("list");
			debug_putchar('\t');
			debug_print("pointer");
			debug_putchar('\t');
			debug_print("top");
			debug_putchar('\t');
			debug_print("stack");
			debug_putchar('\n');
			
			while(ptr != &stlst.running_list)
			{
			process* proc = container_of(ptr, process, prc_list);
			debug_printhex_uint16((size_t)proc);
			debug_putchar('\t');
			debug_printhex_uint16(proc->thr->stack_pointer);
			debug_putchar('\t');
			debug_printhex_uint16(proc->thr->stack_top);
			debug_putchar('\t');
			debug_printhex_uint16((size_t)proc->stack);
			debug_putchar('\n');
			
			ptr=ptr->next;
		};		
		
		};
		