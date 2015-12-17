#include "genos.h"
#include "genos/schedproc/automSched.h"
#include "genos/iostream/iostream.h"
#include "genos/sigslot/delegate2.h"
#include "genos/time/timeserv.h"
#include "genos/debug/debug.h"
#include "genos/platform/aiop2/aiop2.h"
#include "genos_module.h"
#include "avr_mega2560/led_controller.h"
#include "autom_terminal/autom_terminal.h"
using namespace genos;;

Serial_ostream_adapter SOA;
Serial_istream_adapter SIA;
ostream cout (SOA);

LedController leds;
KTerminal KT(SOA, SIA);
automScheduler automSched;


void setup() {
aiop2_init();
automSched.registry(makedelegate(&leds,&LedController::exec));
  automSched.registry(makedelegate(&KT,&KTerminal::exec));
  avr2560_leds_KT_registry(KT,leds);
  proclist_KT_registry(KT);
  leds.change_mode(LEDS_ROUND);

}

void loop() {
automSched.schedule();
timerserv_check();
}