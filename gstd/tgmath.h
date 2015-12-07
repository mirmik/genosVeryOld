#ifndef GENOS_TGMATH
	#define GENOS_TGMATH
	
	
	template<typename valtype>
	valtype tg_pow(valtype base, unsigned int exponent)
	{
		valtype result = 1;
		for (;exponent != 0; exponent--) 
		result *= base;
		return result;
	};
	
	
	
	
	
	
	
	
	
	
	
#endif