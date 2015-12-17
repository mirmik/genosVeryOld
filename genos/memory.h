

#ifndef GENOS_MEMORY_H
	#define GENOS_MEMORY_H

	#include "genos/types.h"
	//#include "genos/debug/debug.h"
	#include "genos/memory/la_alloc.h"
	#include "genos/memory/new.h"
		
	
namespace genos {
	
	
	template<typename T>	T* 		sys_allocate		(size_t n)			
	{return static_cast<T*>(::la_alloc(sizeof(T) * n));};
	
	template<typename T>	void 	sys_deallocate	(T* ptr)	{::la_free((void*)ptr);};
	
	
};
	
	
	
	
	
	
	
#endif