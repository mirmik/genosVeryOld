#ifndef GENOS_TYPENAME
	#define GENOS_TYPENAME
	
	#include "genos/types.h"
	
	
template <typename T> const char* type_name(T&);// { return "unknown"; }    // default

template <typename T> const char* type_name();// { return "unknown"; }    // default	


template<int N> const char* type_name(const char (&) [N]) { return "const char []"; }
//template<size_t N> const char* type_name<char const (&) [N]>() { return "const char []"; }

	
	
	
#endif