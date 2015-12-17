#include "gstd/string.h"
#include "gstd/mem.h"

	void strcpy( char * dst,  const char * src )
	{memcpy(dst, src, gstd::strlen(src));};