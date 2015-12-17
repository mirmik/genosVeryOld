


#ifndef GENOS_EXTERN_ALLOC
#define GENOS_EXTERN_ALLOC

#include <genos/gcontainer/allocator_prototype.h>

namespace genos {


class allocator_malloc : public allocator_prototype {
public:
void* allocate (size_t sz);
void deallocate (void* p);
};

};
extern genos::allocator_malloc malloc_allocator;
#endif