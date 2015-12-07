
#ifndef IOSTREAM_ARD_H
	#define IOSTREAM_ARD_H
	
	#include "Arduino.h"
	
	//#include <genos/platform.h>
	#include <genos/iostream/iostream.h>

	namespace genos{
	
	class Serial_ostream_adapter : public Writer<char>
	{
		public:
		size_t write(char i) {return Serial.write(i);
			//debug_putchar(i);
			return 0;
			};
		
		size_t write(char* i, size_t n) {
			//debug_write(i, n);
			return Serial.write(i, n);
			return 0;
			};
		size_t flush(){};
		
		};
		
		
		class Serial_istream_adapter : public Reader<char>
	{
		size_t read() {
			return (Serial.read());
			};
		size_t available() {
	return (Serial.available());
		};
		
		};
	
		
};
	
	
	
	//extern genos::Serial_basic_ostream_cls Serial_basic_ostream;
	//extern genos::Serial_basic_istream_cls Serial_basic_istream;
	
	
	
	
	
	
	
#endif