

#include "genos/schedproc/process_base.h"
#include "genos/schedproc/scheduler_base.h"

//uint8_t process_operation = READY;
	atomic_t process_operation = 0;
	
	void process_set_running(process_base* proc)
	{
		list_move(&proc->sts_list, &running_list);
		bits_mask_assign(proc->prc_flags, PROC_STATE_MASK, PROC_RUNNING);
	};	
	
	void process_set_wait(process_base* proc)
	{
		list_move(&proc->sts_list, &waiting_list);
		bits_mask_assign(proc->prc_flags, PROC_STATE_MASK, PROC_WAIT);
	};
	
	void process_set_zombie(process_base* proc)
	{
		list_move(&proc->sts_list, &zombie_list);
		bits_mask_assign(proc->prc_flags, PROC_STATE_MASK, PROC_ZOMBIE);
	};
	
	void process_set_stop(process_base* proc)
	{
		list_move(&proc->sts_list, &stop_list);
		bits_mask_assign(proc->prc_flags, PROC_STATE_MASK, PROC_STOP);
	};
	
	void process_init(process_base* proc)
	{
	list_add(&proc->prc_list, &process_list);
	process_set_running(proc);
	};
	
	void process_unbind(process_base* proc)
	{
	list_del(&proc->sts_list);
	list_del(&proc->prc_list);	
	};