#ifndef GENOS_LIST
	#define GENOS_LIST
	
	#include <genos/memory/new.h>
	#include <genos/base_struct/list.h>
	#include <genos/gcontainer/dynamic_obj.h>
	#include <genos/gcontainer/allocator_prototype.h>
	#include <genos/gcontainer/allocator_malloc.h>
	
	namespace genos {
		
		void* outop(list_head* h){return h + 1;};
		
		
		class glist : public dynamic_obj{
			protected:
			size_t elements = 0;
			list_head head;
			allocator_prototype* alloc;
			
			public:	
			glist(size_t _element_size, allocator_prototype* _alloc = &malloc_allocator);
			
			void* _push_back();
			void* _push_front();
			
			void* _push_back_spaced(size_t space);
			void* _push_front_spaced(size_t space);
			
			void _pop_back();
			void _pop_front();
			
			void _pop_back_spaced(size_t space);
			void _pop_front_spaced(size_t space);
			
			size_t size() {return elements;};
			
			template<typename valtype> inline valtype* push_back(valtype V) 
			{return new (static_cast<valtype*> (_push_back())) valtype(V);};
			
			template<typename valtype> inline valtype* push_front(valtype V) 
			{return new (static_cast<valtype*> (_push_front())) valtype(V);};
			
			template<typename valtype> inline valtype* push_back_spaced(size_t space,valtype V) 
			{return new (static_cast<valtype*> (_push_back_spaced(space))) valtype(V);};
			
			template<typename valtype> inline valtype* push_front_spaced(size_t space,valtype V) 
			{return new (static_cast<valtype*> (_push_front_spaced(space))) valtype(V);};
			
			
			class iterator : public abstract_iterator{
				public:
				list_head* current;
				public:
				iterator(list_head* _node) : current(_node) {};		
				
				iterator operator++(int) { iterator i = *this; current=current->next; return i; }
				iterator operator++() { current=current->next; return *this; }
				iterator operator--(int) { iterator i = *this; current=current->prev; return i; }
				iterator operator--() { current=current->prev; return *this; }
				bool operator!= (const iterator& b) {return current != b.current;};
				void* operator*() {return (outop(current));};
				//void* operator->() {return (outop(current));}  //???
			};
			
			class reverse_iterator{
				public:
				list_head* current;
				public:
				reverse_iterator(list_head* _node) : current(_node) {};		
				
				reverse_iterator operator++(int) { reverse_iterator i = *this; current=current->prev; return i; }
				reverse_iterator operator++() { current=current->prev; return *this; }
				bool operator!= (const reverse_iterator& b) {return current != b.current;};
				void* operator*() {return (outop(current));};
				//void* operator->() {return (outop(current));}  //???
			};
			
			iterator begin() {return iterator(head.next);};
			iterator end() {return iterator(&head);};
			
			reverse_iterator rbegin() {return reverse_iterator(head.prev);};
			reverse_iterator rend() {return reverse_iterator(&head);};
			
			
			void delete_nodeobj(list_head* nd, size_t elem);
			list_head* new_nodeobj_after(list_head* nd, size_t elem);
			list_head* new_nodeobj_before(list_head* nd, size_t elem);
			list_head* nodeobj_construct(size_t elem);
		};
		
	};
	
	
	
	
	
#endif