#ifndef GENOS_BASE_STRUCT_DEF_H
	#define GENOS_BASE_STRUCT_DEF_H


#ifndef container_of
#define container_of(ptr, type, member) ({              \
	const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
	(type *)( (char *)__mptr - offsetof(type,member) );})
#endif







#endif