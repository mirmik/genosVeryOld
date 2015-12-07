#ifndef GENOS_READER
	#define GENOS_READER
	
	#include "genos/types.h"
	
	namespace genos{
		
		template<typename T>
		class Reader{public:
			
			
		virtual	size_t read();
		virtual size_t available();
			
			};
		
		
		
		};	
	
#endif