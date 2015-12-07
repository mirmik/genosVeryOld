#include "genos.h"
#include "genos/debug/debug.h"
#include "genos/platform/aiop2/aiop2.h"
#include "genos/schedproc/gSched.h"
#include "genos/time/timerserv.h"

using namespace genos;;

Serial_ostream_adapter SOA;
Serial_istream_adapter SIA;
ostream os (SOA);

gScheduler gSched;
timer_service tmrservice;

int n=0;
ISR(TIMER1_OVF_vect){
    n++;
    if (n==3)
    {
		n=0;
    tmrservice.check();
		gSched.schedule();      
	};
};


void idle(){while(1);};

void task3(){
  digitalWrite(30,1); msleep(200);
  digitalWrite(30,0); msleep(200);
};
void task2(){
	digitalWrite(13,1); msleep(200);
	digitalWrite(13,0); msleep(200);
};

void setup() {
  aiop2_init();
  gSched.init();
	TIMSK1 |= _BV(TOIE1);
	if (!gSched.fork(400)) while(1) task2();
  if (!gSched.fork(400)) while(1) task3();
  if (!gSched.fork(300)) while(1) idle();
	gSched.unblock();
}

void loop() {
	os << "all good" << endl;
	msleep(200); 	
}