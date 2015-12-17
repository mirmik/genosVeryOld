

#ifndef ALLOCATOR_PULL_MANAGER
#define ALLOCATOR_PULL_MANAGER

#include <genos/stl_impl/utility.h>

namespace genos{

class allocator_pull_manager
{
glist alloclist;


allocator_pull_manager() : alloclist(sizeof(std::pair<size_t, allocator_pull*>)) {};

allocator_pull* manage (size_t sz) {};





};









};


#endif