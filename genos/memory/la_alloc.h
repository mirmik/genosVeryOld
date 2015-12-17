#ifndef GENOS_LIST_ALLOC
	#define GENOS_LIST_ALLOC
	
	
	void* la_alloc(size_t sz);
	void la_free(void* ptr);	
	
	void la_debug_info();
	
	extern uint8_t dynamic_memory_debug;
	
	void dynamic_memory_debug_enable();
	
	
	
	
#endif