#include "genos.h"
#include "genos/debug/debug.h"
#include "genos/platform/aiop2/aiop2.h"
#include "genos/schedproc/gSched.h"

using namespace genos;;

gScheduler gSched;

int n=0;
ISR(TIMER1_OVF_vect){
    n++;
    if (n==3)
    {
		n=0;
		digitalWrite(30,1);
		gSched.schedule();      
	};
};

void task2(){
	digitalWrite(13,1); delay(100);
	digitalWrite(13,0); delay(100);
};

void setup() {
	pinMode(13,1);
	TIMSK1 |= _BV(TOIE1);
	if (!gSched.fork(400)) while(1) task2();
	gSched.unblock();
}

void loop() {
	debug_print("loop\n");
	delay(100);
	
}