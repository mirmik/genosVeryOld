

#ifndef DYNAMIC_BUFFER
#define DYNAMIC_BUFFER

#include <genos/gcontainer/dynamic_obj.h>
//#include <genos/alloc.h>
#include "genos/types.h"
#include <genos/gcontainer/allocator_prototype.h>
#include <genos/gcontainer/allocator_malloc.h>


namespace genos {

class dynamic_array{
		protected:
		void* data;
		size_t data_size;
		allocator_prototype* alloc;
		
		dynamic_array() : data(0), data_size(0), alloc(&malloc_allocator)  {};
		
		dynamic_array(allocator_prototype* _alloc) : data(0), data_size(0), alloc(_alloc)  {};
		
		public:
		void reserve(size_t n);    //need more memory!!!
		








};	//class
	
};	//namespace
	
	
#endif