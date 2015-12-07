

#include "genos/schedproc/maSched.h"


int8_t maScheduler::current_thread;
maScheduler* maScheduler::sched; 
int dbgint=0;
uint8_t brsee=1;
void maScheduler_idle()
	{
		debug_print("idle");dln;
		dcntstp(dbgint, 15);
	};
	
	
	void __starter()
	{maScheduler::sched->thr_array[maScheduler::current_thread].starter();};
	
	
