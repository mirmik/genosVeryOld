
#include "genos/schedproc/scheduler_base.h"


	void scheduler_state_lists::process_list_running(process_state_list* proc)
	{
		list_move(&proc->sts_list, &running_list);
		//bits_mask_assign(proc->prc_flags, PROC_STATE_MASK, PROC_RUNNING);
	};	
	
	void scheduler_state_lists::process_list_wait(process_state_list* proc)
	{
		list_move(&proc->sts_list, &waiting_list);
		//bits_mask_assign(proc->prc_flags, PROC_STATE_MASK, PROC_WAIT);
	};
	
	void scheduler_state_lists::process_list_zombie(process_state_list* proc)
	{
		list_move(&proc->sts_list, &zombie_list);
		//bits_mask_assign(proc->prc_flags, PROC_STATE_MASK, PROC_ZOMBIE);
	};
	
	void scheduler_state_lists::process_statelist_unbind(process_state_list* proc)
	{
		list_del(&proc->sts_list);
	};
	
	void process_proclist_unbind(process_base* proc)
	{
		list_del(&proc->prc_list);
	};