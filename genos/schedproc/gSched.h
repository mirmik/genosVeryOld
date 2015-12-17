#ifndef GENOS_SUBST_SCHED
	#define GENOS_SUBST_SCHED
	
	
	#include <genos/subst/subst.h>
	#include <genos/stack/dynamic_stack.h>
	#include <genos/base_struct/list.h>
	
	#include "genos/schedproc/scheduler_base.h"
	#include "genos/schedproc/process_base.h"
	#include "genos/schedproc/state_lists.h"
	
	
	
	class gScheduler : public subst_scheduler_base
	{public:
		//�������:
		list_head* current;		
		
		
		
		//���������, ���������� ���������� � ��������.
		class process : public process_base_with_thread 
		{public:
			list_head sts_list;	
			//operator process_base() {return *this;};
		};	
		
		state_lists<process> stlst; 
		
		
		void process_set_running(process_base* proc){
			ATOMIC(temp);
			stlst.process_set_running((process*)proc);
			DEATOMIC(temp);
		};
		void process_set_wait(process_base* proc){
			ATOMIC(temp);
			stlst.process_set_wait((process*)proc);
			DEATOMIC(temp);
		};
		void process_set_zombie(process_base* proc){
			ATOMIC(temp);
			stlst.process_set_zombie((process*)proc);
			DEATOMIC(temp);
		};
		void process_set_stop(process_base* proc){
			ATOMIC(temp);
			stlst.process_set_stop((process*)proc);
			DEATOMIC(temp);
		};
		
		
		void process_init(process* proc)
		{ATOMIC(temp);
			stlst.process_set_running(proc);
			DEATOMIC(temp);
		};
		
		
		void process_unbind(process* proc);
		
		public:
		//������:
		void init();					//����������� ������� ���� (�������� ����, ��� ����� 
		//������� ����������� �� RAMEND), 
		//���������� � �������
		
		process* fork(size_t stcksize);	//������ ����� ����
		//��������� ������ ���������� �����
		//���������� �������� ����� ������������ ��������  
		//���������� ������ ����
		
		void exit();					//���������� ������� ����.
		
		void schedule(); 				//����������, ����� ������������ (������ �� ����������)
		void proc_go_wait();
		
		//��� ������:
		void print_list();				//����� � Serial ������ ���������
		
		
		//�������:
		void proc_delete(process* proc);//���������� �������. (�������� ������� ���������� ���������.)
		
		//�����������
		gScheduler() {};
	};
	
	
	
#endif				