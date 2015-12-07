#ifndef GENOS_FIFO
	#define GENOS_FIFO
	
	#include "genos/gstl/traits.h"
	#include "genos/gstl/utility.h"
	#include "genos/gstl/allocator.h"
	#include "genos/base_struct/glist_basic.h"
	
	namespace genos{
	
	template <typename valtype>
	valtype* gsptr(monolist_head* list){return reinterpret_cast<valtype*>(list+1);};
	
	template <
	class valtype, 
	class traits_type = elem_traits<valtype>
	>
	class gfifo{		
		
		typedef typename traits_type::	ptr_type 			pointer;
		typedef typename traits_type::	const_ptr_type 		const_pointer;
		typedef typename traits_type::	reference 			reference;
		typedef typename traits_type::	const_reference 	const_reference;
		typedef 						valtype				value_type;
		typedef typename traits_type::	size_type 			size_type;
		typedef typename traits_type::	ptrdiff_t 			difference_type;
		typedef 		 pair<monolist_head, valtype>			pair_t;
		allocator<pair_t>									alloc;
		
		public:
		monolist_head head;
		monolist_head* last;
		
		public:
		gfifo(): last(&head) {};
		
		void queue(valtype val)
		{
			pair_t* ptr = alloc.allocate(1);
			new (ptr) pair_t(monolist_head(), valtype(val));
			last->add_next(&(ptr->first));
			last = &(ptr->first);
		};
		
		valtype dequeue()
		{
			monolist_head* list = head.next;;
			valtype temp = *gsptr<valtype>(list);
			head.next = head.next->next;
			alloc.deallocate(reinterpret_cast<pair_t*>(list));
			if (last == list) last = &head;
			return temp;
		};
		
		bool empty(){return (last->next == &head) ? 1 : 0;};
	};
	
	
	};
	
	
	
#endif