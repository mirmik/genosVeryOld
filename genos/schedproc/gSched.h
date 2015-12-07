#ifndef GENOS_SUBST_SCHED
	#define GENOS_SUBST_SCHED
	

	#include <genos/subst/subst.h>
	#include <genos/stack/dynamic_stack.h>
	#include <genos/base_struct/list.h>
	
	#include "genos/schedproc/scheduler_base.h"
	#include "genos/schedproc/process_base.h"
	
	
	//���������, ���������� ���������� � ��������.
	class process : public process_base_with_thread 
	{};
	
	class gScheduler : public subst_scheduler_base
	{
		//�������:
		list_head* current;		
		
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