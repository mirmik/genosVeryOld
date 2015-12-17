#ifndef GENOS_GSTL__VECTOR
	#define GENOS_GSTL_VECTOR
	
	
	#include <genos/gstl/utility.h>
	#include "genos/gstl/allocator.h"
	
	namespace gstl {
		
		template <
		class valtype, 
		class traits_type = genos::elem_traits<valtype>
		>
		class vector {
			
			typedef typename traits_type::	ptr_type 			pointer;
			typedef typename traits_type::	const_ptr_type 		const_pointer;
			typedef typename traits_type::	reference 			reference;
			typedef typename traits_type::	const_reference 	const_reference;
			typedef 						valtype				value_type;
			typedef typename traits_type::	size_type 			size_type;
			typedef typename traits_type::	ptrdiff_t 			difference_type;
			
			genos::allocator<valtype> alloc;
			
			protected:
			size_type _elements = 0;
			size_type _capacity = 0;
			valtype* data = nullptr;
			
			size_type strategy(size_type need)
			{
				size_type t = 1;
				while(t < need) t<<=1;
				return t;
			};
			
			
			public:
			void resize(size_type n)
			{
				if (n <= _capacity) return;
				size_type new_size = strategy(n);
				valtype* new_data = alloc.allocate(new_size);
				if (data != 0)
				{
					memcpy(new_data, data, _elements * sizeof(valtype));
					alloc.deallocate(data);
				};
				data = new_data;
				_capacity = new_size;
			};
			
			void push_back(const valtype& val)
			{
				resize(_elements + 1);
				new (data + _elements) valtype(val);
				++_elements;
			};
			
		valtype& operator[](size_type i){return *(data + i);};
			
			
		size_type size(){return _elements;};
		size_type capacity(){return _capacity;};
		bool empty(){return _elements == 0;};
			
			
			
			using iterator = valtype*;
			
			
			
			iterator begin(){return data;};
			iterator end(){return data + _elements;};
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		};
		
	};
	
	
#endif