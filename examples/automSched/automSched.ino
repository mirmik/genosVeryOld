#include "genos.h"
#include "genos/iostream/iostream.h"
#include "genos/schedproc/automSched.h"
#include "genos_module.h"
#include "avr_mega2560\led_controller.h"
#include "autom_terminal/autom_terminal.h"

using namespace genos;

Serial_ostream_adapter SOA;
Serial_istream_adapter SIA;
ostream cout (SOA);

LedController leds;
KTerminal KT(SOA, SIA);
timer_service tmrservice;
automScheduler automSched;


void setup() {
	automSched.registry(&leds,&LedController::exec);
	automSched.registry(&KT,&KTerminal::exec);
	avr2560_leds_KT_registry(KT,leds);
	proclist_KT_registry(KT);
	leds.change_mode(LEDS_ROUND);
}

void loop() {
	tmrserv().check();
	scheduler().schedule();
}