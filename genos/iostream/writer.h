#ifndef GENOS_WRITER
	#define GENOS_WRITER
	
	#include "genos/types.h"
	
	namespace genos{
		template<typename T>
		class Writer{
			public:
		virtual	size_t write(T c);
		virtual	size_t write(T* c, size_t n);
		virtual	size_t flush();
			
			};
		
		
		
		};	
	
#endif