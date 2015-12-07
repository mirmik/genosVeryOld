#include "genos.h"
#include "genos/scheduler/maSched.h"
#include "genos/platform/aiop2/aiop2.h"

using namespace genos;;

maScheduler maSched;

int n=0;
ISR(TIMER1_OVF_vect)
{n++;
  if (n==4){n=0;
if (maSched.ready()) maSched.schedule();   };
};

void func1()
{
if (millis() % 1000 < 500) digitalWrite(13,1);
if (millis() % 1000 >= 500) digitalWrite(13,0);
};

void func2()
{
if (millis() % 1000 < 500) digitalWrite(30,1);
if (millis() % 1000 >= 500) digitalWrite(30,0);
};


void setup() {
  init_aiop2();
  aiop2_tmr1_int_on();
  maSched.init();

   maSched.create_func_loop_process(func1, 15, "func1");
   maSched.create_func_loop_process(func2, 15, "func2");
   
  maSched.debug_print_proclist();
  maSched.debug_print_thread_array();
  
  maSched.unblock();
}

void loop() {

}