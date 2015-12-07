

#include "genos/time/timerserv.h"

namespace genos{

timer_service_base* timer_service_base::__tmrserv = nullptr;


timer_service_base& tmrserv() {return *timer_service_base::__tmrserv;};
void tmrserv(timer_service_base& _tmrserv) {timer_service_base::__tmrserv = &_tmrserv;};

};