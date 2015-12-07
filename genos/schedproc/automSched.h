#ifndef GENOS_AUTOM_SCHED
	#define GENOS_AUTOM_SCHED
	
	#include <genos/stack/dynamic_stack.h>
	#include <genos/base_struct/list.h>
	
	#include "genos/schedproc/scheduler_base.h"
	#include "genos/schedproc/process_base.h"
	#include "genos/sigslot/delegate.h"
	
	
	//Структура, содержащая информацию о процессе.
	class process : public process_base 
	{
		public:
		delegate<void> dlg;
	};
	
	class automScheduler : public subst_scheduler_base
	{
		//Ресурсы:
		
		public:
		//Методы:
		void init(){
			unblock();
		};					
		
		
		void schedule(){	//вызов планировщика 
			process* proc;
			
			if(!list_empty(&running_list)) proc = 
			list_entry(running_list.next, process, sts_list);
			else return;
			
			list_move_tail(&proc->sts_list, &running_list);
			proc->dlg();
			return;
		};
		
		
		
		
		void registry(void(*_fnc)(void))
		{
			process* proc = new process;
			proc->dlg = _fnc;
			process_init(proc);
		};
		
		class AbstractDelegated{};
		void registry(void* obj, void(AbstractDelegated::*mtd)())
		{
			process* proc = new process;
			proc->dlg = std::make_pair(obj, mtd);
			process_init(proc);
		};
		
		//Утилиты:
		//void proc_delete(process* proc);//Уничтожить процесс. (Активный процесс уничтожать запрещено.)
		
		//Конструктор
		automScheduler() {init();};
		};
	
	
	
#endif				