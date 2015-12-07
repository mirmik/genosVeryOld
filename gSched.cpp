
#include "genos/debug/debug.h"
#include "genos/schedproc/gSched.h"
#include <genos/base_struct/list.h>
#include "genos/base_struct/bits.h"

	
void gScheduler::init(){
	process* proc = new process;	
	proc->stack = 0;
	proc->thr = new thread;
	proc->thr_flags = THR_NODELETED;
	init_current_thread(proc->thr,RAMEND);
	process_init(proc);	
	current_process(proc);
	bits_clr(sched_flags, NO_INIT);
	current = running_list.next;
};



process* gScheduler::fork(size_t stcksize){
	if (bits_mask_internal_or(sched_flags, NO_INIT)) {return (process*)-1;};
	block_sched();
	process* proc = new process;
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

void gScheduler::exit()
{
	container_of(current, process, prc_list)->prc_flags |= PROC_ZOMBIE; //Доктор сказал в морг
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
		
		current = current->next;
		
	
		strt:
		if (current == &running_list) 					//Проверка на завершение цикла
		if (&running_list == running_list.next)			//Проверка на пустой список
		{debug_panic("Last proccess has been destroyed. HALT");}
		else current = running_list.next;				//Начать новый цикл
		
		proc = container_of(current, process, sts_list);//Указатель на процесс получить.
		
		//if (bits_mask_internal_or(proc->prc_flags, PROC_ZOMBIE)) 		//Если встретили зомби, добили его
		//{current=current->next; proc_delete(proc); goto strt;};
		
		current_process(proc);
		change_thread(proc->thr);
	};
};








//DEBUG

void gScheduler::print_list(){
	
	list_head* ptr = running_list.next;
	Serial.print("list");
	Serial.print('\t');
	Serial.print("pointer");
	Serial.print('\t');
	Serial.print("top");
	Serial.print('\t');
	Serial.print("stack");
	Serial.print('\n');
	
	while(ptr != &running_list)
	{
		process* proc = container_of(ptr, process, prc_list);
		Serial.print((size_t)proc,16);
		Serial.print('\t');
		Serial.print(proc->thr->stack_pointer,16);
		Serial.print('\t');
		Serial.print(proc->thr->stack_top,16);
		Serial.print('\t');
		Serial.print((size_t)proc->stack,16);
		Serial.print('\n');
		
		ptr=ptr->next;
	};		
	
};
