
#ifndef G_ERRSERV_H
#define G_ERRSERV_H

#include <genos/platform.h>

namespace genos {


#ifdef ARDUINO
#define ATOMIC() cli()
#define DEATOMIC() sei()
#endif


enum errno{RINGBUFFER_FULL=0 ,
		RINGBUFFER_EMPTY,
		SUBSTSHED,
		DISP_AUTOMATE};

void sysErr (errno n, int i, void* p);

};








#endif