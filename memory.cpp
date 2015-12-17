

#include "genos/memory.h"

	
#ifdef ARDUINO
	extern char* __malloc_heap_start;
	const char* HEAP_START = __malloc_heap_start;
#endif