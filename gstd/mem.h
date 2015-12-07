#ifndef GENOS_MEMCPY
	#define GENOS_MEMCPY

	
	#include "genos/types.h"
	
namespace gstd{

	void memcpy_diff(void* dst, void* src, size_t len, size_t dest_size);
	//memcpy_diff копирует память из области src в область dst с 
	//явным указанием размера приёмного буфера.
	//Если приёмный буфер меньше пакета, копируется только начало.
	//Если буффер больше пакета, хвост буфера зануляется.


	//void memcpy(void* dst, void* src, size_t len);
	//void memset(void* dst, uint8_t c, size_t len);



};






#endif