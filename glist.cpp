



#include <genos/gcontainer/glist.h>
#include "stdio.h"
#include <string.h>


namespace genos {
	
	glist::glist(size_t _element_size, allocator_prototype* _alloc) : dynamic_obj(_element_size), alloc(_alloc)  {};
	
	
	list_head* glist::nodeobj_construct(size_t elem)
	{
		list_head* newnodeobj = (list_head*) alloc->allocate(sizeof(list_head) + elem);
		return newnodeobj;
	};
	
	
	list_head* glist::new_nodeobj_after(list_head* nd, size_t elem){
		list_head* newnode = nodeobj_construct(elem);
		list_add(newnode, nd);
		return newnode;
	};
	
	list_head* glist::new_nodeobj_before(list_head* nd, size_t elem){
		list_head* newnode = nodeobj_construct(elem);
		list_add_tail(newnode, nd);
		return newnode;
	};
	
	void glist::delete_nodeobj(list_head* nd, size_t elem){
		list_del(nd);
		alloc->deallocate (nd);
	};
	
	
	void* glist::_push_back(){
		return outop(new_nodeobj_after(&head, element_size));
	};
	
	void* glist::_push_front(){
		return outop(new_nodeobj_before(&head, element_size));
	};
	
	
	void* glist::_push_back_spaced(size_t elem){
		return outop(new_nodeobj_after(head.prev, elem + element_size));
	};
	
	void* glist::_push_front_spaced(size_t elem){
		return outop(new_nodeobj_after(&head, elem + element_size));
	};
	
	
	void glist::_pop_back(){
		delete_nodeobj(head.prev, element_size);
	};
	
	
	void glist::_pop_front(){
		delete_nodeobj(head.next, element_size);
	};
	
	
	
	void glist::_pop_back_spaced(size_t outop_size){
		delete_nodeobj(head.prev, element_size + outop_size);
	};
	
	void glist::_pop_front_spaced(size_t outop_size){
		delete_nodeobj(head.next, element_size + outop_size);
	};
	
	
};