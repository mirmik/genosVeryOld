


#ifndef GENOS_ALLOCATOR_PULL
#define GENOS_ALLOCATOR_PULL


#include <genos/container/allocator_prototype.h>
#include <genos/container/allocator_malloc.h>
#include <genos/container/glist.h>

namespace genos {

class pullfreelist{
public:
pullfreelist* next;
pullfreelist(pullfreelist* _next) : next(_next){};
pullfreelist(void* _next) : next(static_cast<pullfreelist*>(_next)){};
//pullfreelist(int _next) : next(static_cast<pullfreelist*>(_next)){};
};
/*
class pullheader{
public:
size_t sz;


};
};*/


class allocator_pull {
public:
const size_t sz;
pullfreelist* first;
allocator_prototype* father;

public:
allocator_pull (size_t _sz) : sz(_sz), first(0), father(&malloc_allocator) {};

	void needmoreminerals()
	{engageblock(strategy());};

	void* allocate (size_t sz) {
	if (first==0) needmoreminerals();//return 0;
	void* temp = first;
	first = first->next;
	return temp;
	};
	
	
	void deallocate (void* p, size_t) {
	pullfreelist* temp = first;
	first = static_cast<pullfreelist*> (p);
	new(first) pullfreelist(temp);
	};
/*
*/
	void engageblock(size_t num)
	{void* newpull = father->allocate(num*sz);
	for(void* i=newpull; i < (newpull+sz*(num-1)); i+=sz)
	new(i) pullfreelist(i+sz);
	new(newpull+sz*(num-1)) pullfreelist(first);
	first = static_cast<pullfreelist*> (newpull);
	};

void print () {
Serial.print((int)this, HEX);Serial.print('\t');Serial.print(sz);Serial.print('\t');Serial.print((int)first,HEX);Serial.print('\n');
pullfreelist* temp = first;
int i=0;
while (temp!=0) {i++; Serial.print(i);Serial.print('\t'); Serial.print((int)temp,HEX);Serial.print('\t');Serial.println((int)temp->next,HEX); temp=temp->next;};
};

size_t strategy()
{if (sz<=8) return 8;
if (sz<=32) return 4;
 return 2;};

};
};
#endif