


#include <genos/gcontainer/gvector.h>
#include "stdio.h"
#include <string.h>
	
	 
	
namespace genos {
	//inline int gvector::strategy(int n){return (n==0 ? 1 : 2*n);}
	inline int gvector::strategy(int n){return (n+1);}

void gvector::resize(size_t sz){
		if(sz > elements){      
			if(sz * element_size > data_size){
				reserve(strategy(elements)*element_size);
			}

//			for(size_t i = elements; i<sz ; ++i){
//				elemcpy(data + i*element_size, x);
//			}
			elements = sz;
//		}else{
//			//downsize(sz);
//		}
	};
	};

inline void gvector::downsize(size_t sz){
		elements = sz;
	};
	
	
void* gvector::_push_back(){
	resize( size() + 1);
	return (data + (elements - 1) * element_size);
};

void gvector::_pop_back(){
	downsize(size() - 1);
};

};