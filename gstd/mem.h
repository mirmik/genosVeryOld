#ifndef GENOS_MEMCPY
	#define GENOS_MEMCPY

	
	#include "genos/types.h"
	
namespace gstd{

	void memcpy_diff(void* dst, void* src, size_t len, size_t dest_size);
	//memcpy_diff �������� ������ �� ������� src � ������� dst � 
	//����� ��������� ������� �������� ������.
	//���� ������� ����� ������ ������, ���������� ������ ������.
	//���� ������ ������ ������, ����� ������ ����������.


	//void memcpy(void* dst, void* src, size_t len);
	//void memset(void* dst, uint8_t c, size_t len);



};






#endif