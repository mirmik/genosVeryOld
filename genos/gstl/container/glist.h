


#ifndef GENOS_GLIST2_H
	#define GENOS_GLIST2_H
	
	#include <genos/gstl/utility.h>
	#include <genos/base_struct/list.h>
	#include "genos/gstl/allocator.h"
	
	namespace gstl{
		
template <
class valtype, 
class traits_type = genos::elem_traits<valtype>
>
		class glist
		{
			
			typedef typename traits_type::	ptr_type 			pointer;
			typedef typename traits_type::	const_ptr_type 		const_pointer;
			typedef typename traits_type::	reference 			reference;
			typedef typename traits_type::	const_reference 	const_reference;
			typedef 						valtype				value_type;
			typedef typename traits_type::	size_type 			size_type;
			typedef typename traits_type::	ptrdiff_t 			difference_type;
			typedef 		 std::pair<list_head, valtype>			pair_t;
			genos::allocator<pair_t>									alloc;
			
			public:
			list_head head;
			
			glist() : head() {};
			
			/*
			 construct() {
				pair_t* ptr = alloc::allocate(1);
				new ((ptr->first)) list_head; 
				return static_cast<list_head*>(ptr);
			};*/
			
			
			pointer push_back(const valtype &val){
				pair_t* ptr = alloc.allocate(1);
				new (ptr) pair_t(list_head(), valtype(val));
				list_add_tail(& ptr->first, &head);
				return &(ptr->second);
			};
			
			pointer push_front(const valtype &val){
				pair_t* ptr = alloc.allocate(1);
				new (ptr) pair_t(list_head(), valtype(val));
				list_add(& ptr->first, &head);
				return &(ptr->second);
			};
						
			void pop_back(){
				list_head* lh = head.prev;
				list_del(lh);
				alloc.deallocate(reinterpret_cast<pair_t*>(lh));				
			};
			
			void pop_front(){
				list_head* lh = head.next;
				list_del(lh);
				alloc.deallocate(reinterpret_cast<pair_t*>(lh));				
			};
			
			
			
			class iterator{
				public:
				list_head* current;
				public:
				iterator(list_head* _head) : current(_head) {};		
				
				iterator operator++(int) { iterator i = *this; current=current->next; return i; }
				iterator operator++() { current=current->next; return *this; }
				iterator operator--(int) { iterator i = *this; current=current->prev; return i; }
				iterator operator--() { current=current->prev; return *this; }
				bool operator!= (const iterator& b) {return current != b.current;};
				bool operator== (const iterator& b) {return current == b.current;};
				
				reference operator*() {return reinterpret_cast<pair_t*>(current)->second;};
				pointer operator->() {return &reinterpret_cast<pair_t*>(current)->second;} 
			};
			
			
			
			
			/*
				class reverse_iterator{
				public:
				nodeobj* current;
				public:
				reverse_iterator(nodeobj* _node) : current(_node) {};		
				
				reverse_iterator operator++(int) { reverse_iterator i = *this; current=current->prev; return i; }
				reverse_iterator operator++() { current=current->prev; return *this; }
				bool operator!= (const reverse_iterator& b) {return current != b.current;};
				bool operator== (const reverse_iterator& b) {return current == b.current;};
				void* operator*() {return (current->outop());};
				//void* operator->() {return (current->outop());}  //???
			};*/
			
			iterator begin() {return iterator(head.next);};
			iterator end()   {return iterator(&head);};
			
			/*
				reverse_iterator rbegin() {return reverse_iterator(head.prev);};
				reverse_iterator rend() {return reverse_iterator(&head);};
			*/
			/*
			iterator erase(iterator it){
				list_head* lh = it.current;
				it++;
				lh->unbind();
				alloc->deallocate(lh,0);
				return it;
			};
			
			void delete_listedobj(valtype* p)
			{
				iterator it(get_list_from_obj(p));		
				erase(it);
			};*/
		};
		
		
		
		
	};
	
#endif