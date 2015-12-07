#ifndef GENOS_INFO
	#define GENOS_INFO
	
	
#include <genos/iostream/iostream.h>
//#include <genos/process/base_proc.h>

#include <genos/subst/subst.h>
#include <genos/subst/thread_constructor.h>

#include <genos/schedproc/maSched.h>
#include <genos/schedproc/gSched.h>

//#include <genos/subst/subst_sched.h>
//#include <genos/gmath/gfloat.h>
	
	
	
	//ostream& operator<< (ostream& o, uint8_carry &uc);
	//ostream& operator<< (ostream& o, uint16_carry &uc);
	//ostream& operator<< (ostream& o, gfloat &uc);
	//ostream& operator<< (ostream& o, gfloat &&uc);
	
	
	genos::ostream& operator<< (genos::ostream& o, thread& thr);
	//genos::ostream& operator<< (genos::ostream& o, process& thr);
	
	
	//void os_print_proclist(genos::ostream& os);
	
	
	//subst INFO
	void debug_info(thread &thr);
	void debug_info(thread_constructor &tc);
	
	/// maSched INFO
	//0 - информация о нитях
	//1 - информация о процессах
	void debug_info(maScheduler &ma, int i);
	void debug_info(maScheduler::thread_manager &tm);
	
	
	
	
#endif