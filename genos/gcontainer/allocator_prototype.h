

#ifndef GENOS_ALLOCATOR_PROTOTYPE
#define GENOS_ALLOCATOR_PROTOTYPE


#include <genos/types.h>

namespace genos {


class allocator_prototype
{
public:
virtual void* allocate (size_t sz);
virtual void deallocate (void* p);

virtual size_t getFreeMemory(){};

virtual void* rebind(){};
virtual void engage(){};
};

};

#endif