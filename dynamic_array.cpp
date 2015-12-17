	
	
	
#include <genos/gcontainer/dynamic_array.h>
#include <gstd/mem.h>
	
namespace genos {
	
		allocator_prototype* alloc;
	
	
	void dynamic_array::reserve(size_t n){
		if(n > data_size){              //We never shrink...
			void* temp_ptr = data;
			size_t temp_size = data_size;

			data_size = n;
			data =  alloc->allocate(data_size);
	
			memcpy(data, temp_ptr, temp_size);	
//if (temp_ptr==0) - its allocator problems....			
			//genos::deallocate (data, temp_size);
			alloc->deallocate (temp_ptr);
		}
	}
	
	
	
	
	
	
	
	};
	