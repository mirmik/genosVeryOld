

#include "gstd/mem.h"


void memcpy(void* s1, const void* s2, size_t len)
{
	char* dst = (char*) s1;
	char* src = (char*) s2;
	
	while(len--) *dst++ = *src++;	
};