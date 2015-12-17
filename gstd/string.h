
#ifndef GENOS_CSTD_STRING
	#define GENOS_CSTD_STRING
	
	
	#include "genos/debug/debug.h"
	#include "genos/types.h"
	
	namespace gstd{
		
		size_t strlen ( const char * str );
		size_t strcpy ( char * dst,  const char * str );
		
		
		
	template<size_t N>
	class static_string
	{public:
		
		char* cursor;	
		char data[N];	
		
		static_string() : cursor(data) {};
		
		static_string(const char* c) : cursor(data) {*this += c;};
		
		void operator+=(const char* c)
		{
			for(;*c != '\0';)*cursor++ = *c++;
			if (cursor >= (data + N)) debug_panic ("static_string_ovf");
		};
		
		void operator+=(char c)
		{
			*cursor++ = c;
			if (cursor >= (data + N)) debug_panic ("static_string_ovf");
		};
		
		char* to_cstr(){*cursor = '\0'; return data;};
		
		//operator char*() {return to_cstr();};
	};
	
	template<size_t N>
	class static_revstring
	{public:
			
		char* cursor;
		char data[N];	
		
		static_revstring() : cursor(data + N) {*--cursor = '\0';};
		
		static_revstring(char* str) : cursor(data + N) {*--cursor = '\0'; *this += str;};
		
		void operator-=(const char* c)
		{
			for(;*c != '\0';)*--cursor = *c++;
			if (cursor < (data)) debug_panic ("static_string_ovf");
		};
		
		void operator+=(const char* c)
		{
			const char* d = c;
			for(;*d!='\0'; ++d);
			for(;d != c;)*--cursor = *--d;
			if (cursor < (data)) debug_panic ("static_string_ovf");
		};
		
		void operator+=(char c)
		{
			*--cursor = c;
			if (cursor < (data)) debug_panic ("static_string_ovf");
		};
		
		char* to_cstr(){return cursor;};
		
		//operator char*() {return to_cstr();};
	};
		
		
		
		
		template<typename NumType>
		static_revstring<21> int_to_string(NumType num, size_t base)
		{
			size_t exscess;
			static_revstring<21> str;
			bool negative = num < 0;
			if (num == 0) str+='0'; 
			if (num < 0) {num = -num;};
			for (; num != 0; num /= base)
			{
				exscess = (num % base);
				str += (exscess + ((exscess <= 9) ? '0' : ('A' - 0x0A)));
			};
			if (negative) str += '-';
			return str;	
		};
		
		
		
	
		
		
		
		
		
		
		
		
		
	};
		
		
	#endif	