#ifndef GENOS_AUTOM_SCHED
	#define GENOS_AUTOM_SCHED
	
	#include <genos/stack/dynamic_stack.h>
	#include <genos/base_struct/list.h>
	
	#include "genos/schedproc/scheduler_base.h"
	#include "genos/schedproc/process_base.h"
	#include "genos/sigslot/delegate.h"
	#include "genos/debug/debug_info.h"
	
	
	//���������, ���������� ���������� � ��������.
	class process : public process_base 
	{
		public:
		delegate<void> dlg;
	};
	
	
	class automScheduler : public subst_scheduler_base
	{
		//�������:
		uint8_t proc_is_unbind;
		public:
		//������:
		void init(){
			unblock();
		};					
		
		
	void proc_go_wait()
	{
		proc_is_unbind = 1;
	};
		
		int a;
		void schedule(){	//����� ������������ 
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
		
		//�������:
		//void proc_delete(process* proc);//���������� �������. (�������� ������� ���������� ���������.)
		
		//�����������
		automScheduler() : proc_is_unbind(0) {init();};
		};
	
	
	
#endif				