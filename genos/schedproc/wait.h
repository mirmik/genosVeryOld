#ifndef GENOS_WAIT_H
	#define GENOS_WAIT_H
	
	#include "genos/schedproc/scheduler_base.h"
	#include "genos/schedproc/process_base.h"
	
	namespace genos{
		
		//Довольно бесполезный класс... 
		class __waiter_basic{
			public:
			void unwait();
			void wait();
		};
		
		
		class easy_waiter : public __waiter_basic
		{public:
			process_base* proc;
			
			void unwait(){
				process_operation = 1;
				process_set_running(proc);
				process_operation = 0;
			};
			
			void unwait_reschedule(){
				unwait();
				scheduler()->schedule();
			};
			
			void wait_automate()	{
				process_operation = 1;
				proc = current_process(); 
				scheduler()->proc_go_wait();
				process_set_wait(proc);
				process_operation = 0;
			};
			
			void wait()	{
				wait_automate();
				scheduler()->schedule();
			};
			
			
		};
		
		
		
		
		
	};
	
	
	
	
	
	
	
#endif