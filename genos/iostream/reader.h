#ifndef GENOS_READER
	#define GENOS_READER
	
	#include "genos/types.h"
	
	namespace genos{
		
		class Reader{
			
			
		virtual	size_t read(char c);
		virtual	size_t read(char* c, size_t n);
		virtual size_t available();
			
			};
		
		
		
		};	
	
#endif