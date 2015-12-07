


#include <genos/iostream/char_traits.h>

namespace genos{
	
	
	
	
	
	
	
	
	template<>
	size_t char_traits<char>::length(char* c)
	{
		int n=0;
		while(*(c++)!=0) n++;
		return n;
		}
	
	
};
	
	
	
	
	
	
	
	
	
	
	
	
