
#include "genos/stack/dynamic_stack.h"
#include "genos/memory.h"

	

	
	dynamic_stack* construct_dynamic_stack(size_t size){
		void* ptr = genos::sys_allocate<void>(sizeof(dynamic_stack) + size);
		static_cast<dynamic_stack*>(ptr)->size=size;
		return static_cast<dynamic_stack*>(ptr);
	}
	
	
	
	