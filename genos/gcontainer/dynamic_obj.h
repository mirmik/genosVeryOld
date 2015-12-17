
#ifndef DYNAMIC_OBJ
#define DYNAMIC_OBJ

//#include <genos/alloc.h>
#include "genos/types.h"

namespace genos {

class dynamic_obj {
		protected:
		const size_t element_size;
		
		dynamic_obj(size_t _element_size) : 
		element_size(_element_size)		
		{};
		
		public:		
		
		size_t elemsize() {return element_size;};
		//void elemcpy(void* dest,void* src) ;
};	//class

class abstract_iterator {
	public:
	virtual void* operator*();
	};
	
};
	
	
template<typename valtype> inline valtype& get_obj(genos::abstract_iterator &it) {return *static_cast<valtype*>(*it);};
template<typename valtype> inline valtype* get_objptr(genos::abstract_iterator &it) {return static_cast<valtype*>(*it);};
	
	
	
#endif