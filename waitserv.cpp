

#include "genos/wait/waitserv.h"
#include "genos/base_struct/bits.h"
//#include "genos/debug/debug_info.h"


list_head wait_list;

bool wait_check(wait* wt){
	switch(bits_mask(wt->trait, wt::WAITTYPE))
	{
		case wt::FLAG8:
		return (*htreat<uint8_t*>(wt->info_cond) != 0);		
		break;
		
		#ifdef IOSTREAM_MODE
			case wt::INPUT_STREAM:
			return (htreat<genos::Reader<char>*>(wt->info_cond)->available() != 0);		
			break;
		#endif
		
		#ifdef DEBUG_MODE
			default: debug_panic("waitserv, check"); break;
		#endif
	};
	
	
	
};

void wait_exec(wait* wt){
	switch(bits_mask(wt->trait, wt::TASKTYPE))
	{
		case wt::FUNC_VOID:
		htreat< void(*)() >(wt->info_task)();		
		break;
		
		#ifdef DELEGATE_WT
			case wt::DELEGATE_VOID:
			htreat<waitserv_d<void>>(wt->info_task)();		
			break;
		#endif
		
		#ifdef PROCESS_MODE
			case wt::PROC_WAIT:
			htreat< std::pair <process_base*, scheduler_base*>>(wt->info_task).second
			-> process_set_running
			(htreat< std::pair <process_base*, scheduler_base*>>(wt->info_task).first); 		
			break;
		#endif
		
		#ifdef DEBUG_MODE
			default: debug_panic("waitserv, exec"); break;
		#endif
	};	
};

void destroy_wait(wait* wt){
	list_del(&wt->wt_list); delete(wt);
};

void waitserv_check()
{	
	ATOMIC(temp);
	wait* wt, *tmp;
	list_for_each_entry_safe(wt, tmp, &wait_list, wt_list)
	{
		if (wait_check(wt)) {wait_exec(wt); destroy_wait(wt);};
	};
	DEATOMIC(temp);
};	




#ifdef PROCESS_MODE
	void wait_autom(uint8_t* flag){
		ATOMIC(temp);
		scheduler()->process_set_wait(current_process()); 
		wait_create_procwait(current_process(), scheduler(), flag, wt::FLAG8);
		DEATOMIC(temp);
	};
	
	void wait_subst(uint8_t* flag){
		ATOMIC(temp);
		scheduler()->process_set_wait(current_process()); 
		wait_create_procwait(current_process(), scheduler(), flag, wt::FLAG8);
		scheduler()->schedule();
		DEATOMIC(temp);
	};
	#ifdef IOSTREAM_MODE
		void wait_autom(genos::Reader<char>* flag){
			ATOMIC(temp);
			scheduler()->process_set_wait(current_process()); 
			wait_create_procwait(current_process(), scheduler(), flag, wt::INPUT_STREAM);
			DEATOMIC(temp);
		};
		
		void wait_subst(genos::Reader<char>* flag){
			ATOMIC(temp);
			scheduler()->process_set_wait(current_process()); 
			wait_create_procwait(current_process(), scheduler(), flag, wt::INPUT_STREAM);
			scheduler()->schedule();
			DEATOMIC(temp);
		};
	#endif
	#else
	void wait_autom(uint8_t* flag){};
	void wait_subst(uint8_t* flag){};
	#ifdef IOSTREAM_MODE
		void wait_autom(genos::Reader<char>* flag){};
		void wait_subst(genos::Reader<char>* flag){};
	#endif
#endif







