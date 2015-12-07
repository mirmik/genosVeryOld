#ifndef GENOS_DEBUG_PRINT
	#define GENOS_DEBUG_PRINT
	
#include <genos/types.h> 

/*	
	2012-2015 Mirmik
	Библиотека низкоуровневого отладочного вывода.
	
	Библиотека предназначена для облегчения низкоуровневой отладки.
	Функции не имеют внешних зависимостей (кроме определения типов), 
	линкуются по стандарту "С", что позволяет
	вызывать их в том числе с использованием ассемблера. 
	
	Библиотека призвана помочь в создании плацдарма на неосвоенном железе,
	а так же при отладке средств ввода-вывода.
	
	Для подключения библиотеки необходимо реализовать платформозависимую функцию
	debug_putchar, выводящую один символ char и 
	блокирующую процессор на время проведения этой операции.
*/




#ifdef __cplusplus   
extern "C" {
#endif

void debug_print_init();

//Платформозависимый !блокирующий процессор! вывод char
 void debug_putchar(char c);

//Вывод строки указанной длины.
 void debug_write(const char* c,int i);
//Вывод интов, согласно типам. Возможен вывод в системах dec, hex, bin.
 void debug_printhex_uint4(uint8_t b);
 void debug_printhex_uint8 (uint8_t b);
 void debug_printhex_uint64(uint64_t a);
 void debug_printhex_uint32(uint32_t a);
 void debug_printhex_uint16(uint16_t a);
 void debug_printbin_uint4 (uint8_t b);
 void debug_printbin_uint8 (uint8_t b);
 void debug_printbin_uint64(uint64_t a);
 void debug_printbin_uint32(uint32_t a);
 void debug_printbin_uint16(uint16_t a);
 void debug_printdec_uint8 (uint8_t b);
 void debug_printdec_uint64(uint64_t a);
 void debug_printdec_uint32(uint32_t a);
 void debug_printdec_uint16(uint16_t a);
 void debug_printdec_int8 (int8_t b);
 void debug_printdec_int64(int64_t a);
 void debug_printdec_int32(int32_t a);
 void debug_printdec_int16(int16_t a);

static inline void debug_printdec_uint32(uint32_t x){debug_printdec_uint64((uint64_t)x);};
//strlen для внутреннего использования
 int debug_strlen(const uint8_t *c);

//Вывод нульформатированной строки
 void debug_print(const char *c);

//?????? 
// void debug_print_memory_as_byte(int64_t start,int64_t count);
// void debug_print_memory_as_char(int64_t start,int64_t count);

//Вывод дампа памяти. size - размер в байтах.
 void debug_print_dump(void* address, uint32_t size);

//Вывод логического значения.
 void debug_print_bool(bool b);
 void debug_print_bool_num(bool b);

//Вывод float одинарной точности. //TODO дополнить
 void debug_printbin_spf(sp_float a);


//TODO проверка функций библиотеки debug_print.
// void debug_print_test();

//Тесты для проверки ассемблерной линковки.
 void debug_link_test();
 void debug_link_test_uint16_get2(uint16_t a, uint16_t b);
 void debug_link_test_uint16_get4(uint16_t a, uint16_t b, uint16_t c, uint16_t d);
 uint16_t debug_link_test_uint16_ret();
 uint64_t debug_link_test_uint64_ret();


#ifdef __cplusplus 
};
#endif
#endif