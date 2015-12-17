
#include "genos/debug/debug.h"
#include "genos/schedproc/scheduler_base.h"
#include <genos/base_struct/list.h>
#include "genos/base_struct/bits.h"
#include "genos/syscontext/syscontext.h"


bool scheduler_base::ready(){
	return (bits_mask_internal_or(sched_flags, BLOCK_MASK) || !CAN_SUBST)  ? false : true; 
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
	stack = construct_dynamic_stack(size_of_stack);		//������������ ���� ������� �������
	thr = new thread;									//������������ ����.
	set_stack_thread(thr, stack->top());				//������� ���� ����.
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
	if ((thr_flags & THR_NODELETED)!=THR_NODELETED){				//���� ���� �� ���������,					
	free(stack);};										//�� ���������� ����.
	delete thr;											//�, � ����� ������, ���������� ����
};












