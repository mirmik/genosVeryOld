#ifndef GENOS_SCHEDULER_BASE
	#define GENOS_SCHEDULER_BASE
	
	#include <genos/debug/debug.h>
	#include <genos/base_struct/list.h>
	#include <genos/subst/subst.h>
	#include <genos/schedproc/process_base.h>
	
	#include "genos/subst/thread_constructor.h"
	
	
	
	static constexpr uint8_t USER_BLOCK	=	0x01;
	static constexpr uint8_t SCHED_BLOCK=	0x02;
	static constexpr uint8_t NO_INIT	=	0x04;
	static constexpr uint8_t BLOCK_MASK	=	0x0F;
	
	
		//��������� ������ ���������
		extern list_head process_list;
		extern list_head running_list;
		extern list_head waiting_list;
		extern list_head zombie_list;
		extern list_head stop_list;
	
	
	process_base* current_process();
	void current_process(process_base*);
	
	
	///�����������. ������� �����.
	class scheduler_base
	{public:
		uint8_t sched_flags;					//������� ������������
		
		static scheduler_base* __sched;
		
		
		friend scheduler_base& scheduler();
		friend void scheduler(scheduler_base& _sched);
				
		void block();					//������� ���������� ������������
		void unblock();				
		
		//������:
		bool ready();					//���������� ���������� � ������������.
										//����������� �� �����, ���� ���������� 
										//���� �� ����� � BLOCK_MASK ���� 
										//�� �������� ���������� process_operation
		
		
		//���������� ���������� ��� ������ ������� ��������, ���� waiter
		virtual void schedule()=0;
		virtual void proc_go_wait(){};
		scheduler_base() : sched_flags(NO_INIT) {if (__sched!= nullptr) debug_panic("Second scheduler!");__sched=this;};
		};
	
	
	
	
	
	///����������� ������������ ������������. ������� �����.
	class subst_scheduler_base : public scheduler_base
	{public:
		//�������:	
		
		//�������:
		void block_sched();				//���������� ���������� ������������
		void unblock_sched();			
		
		//�����������
		subst_scheduler_base() {bits_set(sched_flags, USER_BLOCK);}; 
	};	
	
	
	void debug_all_list_print();
	void debug_process_list_print();
	void debug_running_list_print();
	void debug_waiting_list_print();
	void debug_zombie_list_print();
	void debug_stop_list_print();
	
		
	
	scheduler_base& scheduler();
	void scheduler(scheduler_base& _sched);
	void move_tail_running_list(process_base* proc);
	
#endif