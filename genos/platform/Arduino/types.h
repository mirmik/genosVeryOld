#ifndef GENOS_ARDUINO_TYPES
	#define GENOS_ARDUINO_TYPES

#define VOID_PTR_SIZE 2
	
#define 	__CONCATenate(left, right)   left ## right
#define 	__CONCAT(left, right)   __CONCATenate(left, right)

#define offsetof(type,member) ((size_t) &(((type*)0)->member))

typedef unsigned int size_t;
#ifndef ARDUINO
typedef size_t ptrdiff_t;
#endif
typedef signed char atomic_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;
typedef signed long long int64_t;

typedef int64_t intmax_t;
typedef int16_t intptr_t;

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;

typedef uint64_t uintmax_t;
typedef uint16_t uintptr_t;

typedef uintmax_t __umax_int_t;
typedef float sp_float;

typedef decltype(nullptr) nullptr_t;
#define NULL nullptr

#define INT8_MAX 0x7F
#define INT16_MAX 0x7fff
#define INT32_MAX 0x7fffffffL
#define INT64_MAX 0x7fffffffffffffffLL

#define INT8_MIN 	(-INT8_MAX - 1)
#define INT16_MIN 	(-INT16_MAX - 1)
#define INT32_MIN 	(-INT32_MAX - 1L)
#define INT64_MIN 	(-INT64_MAX - 1LL)

#define UINT8_MAX 	(INT8_MAX * 2 + 1)
#define UINT16_MAX 	(__CONCAT(INT16_MAX, U) * 2U + 1U)
#define UINT32_MAX  (__CONCAT(INT32_MAX, U) * 2UL + 1UL)
#define UINT64_MAX  (__CONCAT(INT64_MAX, U) * 2ULL + 1ULL)

#define 	INTPTR_MAX   INT16_MAX
#define 	INTPTR_MIN   INT16_MIN
#define 	UINTPTR_MAX   UINT16_MAX
#define 	INTMAX_MAX   INT64_MAX
#define 	INTMAX_MIN   INT64_MIN
#define 	UINTMAX_MAX   UINT64_MA
#define 	PTRDIFF_MAX   INT16_MAX
#define 	PTRDIFF_MIN   INT16_MIN
#define 	SIG_ATOMIC_MAX   INT8_MAX
#define 	SIG_ATOMIC_MIN   INT8_MIN
#define 	SIZE_MAX   UINT16_MAX
#endif