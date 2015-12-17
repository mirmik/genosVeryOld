#ifndef GENOS_VECTOR
#define GENOS_VECTOR

#include <genos/memory/new.h>
#include <genos/gcontainer/dynamic_array.h>

namespace genos {

class gvector : public dynamic_array, dynamic_obj{
		protected:
			size_t elements;
		
		public:
			gvector(size_t _element_size) : dynamic_obj(_element_size), dynamic_array(), elements(0) {};
			void resize(size_t n);
			void* _push_back();
			void _pop_back();

			template<typename valtype> inline valtype* push_back(valtype& V) 
			{return new (static_cast<valtype*> (_push_back())) valtype(&V);};
			template<typename valtype> inline valtype* push_back(valtype V) 
			{return new (static_cast<valtype*> (_push_back())) valtype(V);};
	
			size_t size() {return elements;};
			size_t capasity() {return (data_size);};
		
			inline void downsize(size_t sz);
			inline int strategy(int n);
		
			void* operator[] (size_t n) {return (data + n * element_size);};

			typedef void* weak_iterator;
		
			class iterator : public abstract_iterator{
				public:
					void* current;
					size_t sz;
				public:
					iterator(void* p, size_t _sz) : current(p) , sz(_sz) {};		
		
					iterator operator++(int) { iterator i = *this; current=current+sz; return i; }
					iterator operator++() { current=current+sz; return *this; }
					bool operator!= (const iterator& b) {return current != b.current;};
					void* operator*() {return (current);};
		};
		
		weak_iterator begin_ptr() {return data;};
		weak_iterator end_ptr() {return data + elements * element_size;};
		
		iterator begin() {return iterator(data,element_size);};
		iterator end() {return iterator(data + data_size, element_size);};
		
		
		};

};






#endif