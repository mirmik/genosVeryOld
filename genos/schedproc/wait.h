#ifndef GENOS_WAIT_H
	#define GENOS_WAIT_H
	
	#include "genos/schedproc/scheduler_base.h"
	#include "genos/schedproc/process_base.h"
	
	namespace genos{
		
		//Èםעונפויס... 
		class waiter_basic{
			public:
			virtual void unwait()=0;
			virtual void wait()=0;
		};
		
		
		class easy_waiter : public waiter_basic
		{public:
			process_base* proc;
			
			void unwait(){
				process_operation = 1;
				dpr("unwait");debug_printhex_ptr(proc);
				process_set_running(proc);
				process_operation = 0;
			};
			
			void unwait_reschedule(){
				unwait();
				scheduler().schedule();
			};
			
			void wait_automate()	{
				process_operation = 1;
				proc = current_process(); 
				scheduler().proc_go_wait();
				process_set_wait(proc);
				debug_print("wait");debug_printhex_ptr(proc);
				process_operation = 0;
			};
			
			void wait()	{
				wait_automate();
				scheduler().schedule();
			};
			
			
		};
		
		
		
		
		
	};
	
	
	
	
	
	
	
#endif