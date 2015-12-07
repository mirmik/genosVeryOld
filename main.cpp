

#include "genos.h"
#include "genos/debug/debug.h"
#include "genos/subst/subst.h"
#include "genos/platform/init.h"


using namespace genos;;


int main ()

{
	init();	
	Serial.begin(9600);
	//debug_print("Genos main\n");
	setup();
	
	while(1) loop();
	
}	