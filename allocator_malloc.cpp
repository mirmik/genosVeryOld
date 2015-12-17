

#include <genos/gcontainer/allocator_malloc.h>
#include <genos/memory/la_alloc.h>

namespace genos {


void* allocator_malloc::allocate (size_t sz) {return la_alloc(sz);};
void allocator_malloc::deallocate (void* p) {la_free(p);};

size_t getFreeMemory(){};

};

genos::allocator_malloc malloc_allocator;