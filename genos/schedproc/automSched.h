#ifndef GENOS_AUTOM_SCHED
	#define GENOS_AUTOM_SCHED
	
	#include <genos/stack/dynamic_stack.h>
	#include <genos/base_struct/list.h>
	
	#include "genos/schedproc/scheduler_base.h"
	#include "genos/schedproc/process_base.h"
	#include "genos/sigslot/delegate.h"
	#include "genos/debug/debug_info.h"
	
	
	//Структура, содержащая информацию о процессе.
	class process : public process_base 
	{
		public:
		delegate<void> dlg;
	};
	
	
	class automScheduler : public subst_scheduler_base
	{
		//Ресурсы:
		uint8_t proc_is_unbind;
		public:
		//Методы:
		void init(){
			unblock();
		};					
		
		
	void proc_go_wait()
	{
		proc_is_unbind = 1;
	};
		
		int a;
		void schedule(){	//вызов планировщика 
			process* proc;
			
			if(list_empty(&running_list)) return; 
			proc = 
			list_entry(running_list.next, process, sts_list);
			list_move_tail(&proc->sts_list, &running_list);
			current_process(proc);			
			proc->dlg();
			
			return;
		};
		
		
		
		
		void registry(void(*_fnc)(void))
		{
			process* proc = new process;
			proc->dlg = _fnc;
			process_init(proc);
		};
		
		template <typename T>
		void registry(T* obj, void(T::*mtd)())
		{
			process* proc = new process;
			proc->dlg = std::make_pair(obj, mtd);
			process_init(proc);
		};
		
		//Утилиты:
		//void proc_delete(process* proc);//Уничтожить процесс. (Активный процесс уничтожать запрещено.)
		
		//Конструктор
		automScheduler() : proc_is_unbind(0) {init();};
		};
	
	
	
#endif				