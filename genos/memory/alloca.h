

#ifndef GENOS_ALLOCA
	#define GENOS_ALLOCA
	
	/*
	
	template<size_t N>
	struct __alloca
	{
		uint8_t array[N];
	};
		
	#define alloca(ptr, T, N) {__alloca<N> __alloca_obj; \
	ptr = (T*)&__alloca_obj;}   
			
	*/
	
#endif