
//2012-2015 Mirmik 
//Реализация функций вытеснения контекста процессора.
//Протестировано на AVR2560

//#pragma GCC optimize "-O0"
#include "genos/debug/debug.h"
#include "genos/subst/subst.h"

	thread* __current;			//Указатель на активную нить.
	//Для внутреннего использования:
	size_t sp_temp;
	thread* __operated;			//Указатель на нить относительно которой выполняется операция.
	
	
	//*******************************************************************************************//
	//									Менятель контекста										 //
	//*******************************************************************************************//
	//Black magic
	
	void substitution ()__attribute__((__noinline__));
	void substitution () 				//Рабочая лошадка. Меняет контекст.
	{											//при вызове в __operated должен быть  
												//адрес активируемой нити.
		PUSH_PROCESSOR_STATE_TO_STACK();		//Сохранить регистры в стек.
		__current -> stack_pointer = readSP();	//Сохранить указатель стека.
		__current = __operated;					//Сменить дескриптор активной нити.
		setSP(__current -> stack_pointer);		//Загрузить указатель стека.
		POP_PROCESSOR_STATE_FROM_STACK();		//Загрузить регистры из стека.
	};
	
	
	//*******************************************************************************************//
	//								Вызов смены нити										 //
	//*******************************************************************************************//
	void change_thread(thread* thr)		//Оболочка для substitution
	{									//адаптированная к внешнему использованию.
		__operated = thr;
		substitution();
	};
	
	//*******************************************************************************************//
	//								Инициализация активной нити									 //
	//*******************************************************************************************//
	void init_current_thread(thread* thr, size_t stcktop)
	{	
		__current = thr;						//Ассоциация this с активной нитью
		set_stack_thread(thr, stcktop);		//Установка stack_top
	};
	
	
	void set_stack_thread(thread* thr, size_t stcktop)
	{
		thr -> stack_top      = stcktop;
		thr -> stack_pointer  = stcktop;
		};
	
	//*******************************************************************************************//
	//								Копирование состояния нити									 //
	//*******************************************************************************************//
	void copy_thread(thread* dst, thread* src)
	{		
		
		//Расчет адресов для операции копирования.
		uint8_t* begin = 	(uint8_t*)src->stack_top + 1;
		uint8_t* end =	 	(uint8_t*)src->stack_pointer;
		
		uint8_t* dst_ptr = 	(uint8_t*)dst->stack_top + 1;
		uint8_t* src_ptr = begin;
		
		//Копируем содержимое стека источника в новый стек.
		for(; src_ptr != end ;) *--dst_ptr = *--src_ptr;
		
		//Под конец вычисляем stack_pointer инициализированного процесса.
		dst->stack_pointer = dst->stack_top - (begin - end - 1);
		
		//debug_print_dump((void*)dst->stack_pointer, dst->stack_top - dst->stack_pointer);
		//debug_print_dump((void*)src->stack_pointer, src->stack_top - src->stack_pointer);
		//debug_stop();
	};
	//*******************************************************************************************//
	//								Копирование состояния текущей нити							 //
	//*******************************************************************************************//
	//Внутренняя функция. Непосредственная реализация здесь.
	void __fork_thread(thread* dst)__attribute__((noinline));
	void __fork_thread(thread* dst)
	{	
		sp_temp = readSP();
		__operated = dst;							//После следующей операции локальные переменные
													//станут недоступны, так что переносим 
													//адрес потомка в глобальную переменную.
		PUSH_PROCESSOR_STATE_TO_STACK();			//Скидываем регистры в стек.
		__current -> stack_pointer = readSP();		//Устанавливаем в дескрипторе значение 
													//Stack Pointer
													//Теперь состояние нити соответствует спящему.
		copy_thread(__operated, __current);		//Копируем усыплённую нить в нить потомка.
		setSP(sp_temp);							//Возвращаем состояние процессора к исходному.
		//POP_PROCESSOR_STATE_FROM_STACK();
	};
	
	//Оболочка функции копирования активной нити.
	//Пролог и эпилог, обеспечивают возврат различных значений.
	//Возвращает ноль для потомка, единицу для предка
	int fork_thread(thread* dst)
	{	
		thread* parent = __current;				//Запоминаем дескриптор родителя.		
		__fork_thread(dst);					    //Выполняем копирование активной нити.
		return (__current == parent ? 1 : 0);	//Сравниваем текущую активную нить с дескриптором родителя.
	};
	
	
	
	//*******************************************************************************************//
	//								Копирование части стека										 //
	//*******************************************************************************************//
	void copy_part_thread(thread* dst, thread* src, size_t copy_count);
	void copy_part_thread(thread* dst, thread* src, size_t copy_count)
	{		
		//Расчет адресов для операции копирования.
		uint8_t* begin = 	(uint8_t*)src->stack_pointer + copy_count + 1;
		uint8_t* end =	 	(uint8_t*)src->stack_pointer;
		
		uint8_t* dst_ptr = 	(uint8_t*)dst->stack_top + 1;
		uint8_t* src_ptr = begin;
		
		//Копируем содержимое стека источника в новый стек.
		for(; src_ptr != end ;) *--dst_ptr = *--src_ptr;
		
		//Под конец вычисляем stack_pointer инициализированного процесса.
		dst->stack_pointer = dst->stack_top - (begin - end - 1);
		//debug_print_dump((void*)dst->stack_pointer, dst->stack_top - dst->stack_pointer);
		//debug_print_dump((void*)src->stack_pointer, src->stack_top - src->stack_pointer);
		//debug_printhex_uint16((uint16_t)(exec_thread));dln;
		//debug_printhex_uint16((uint16_t)(__exec_thread));dln;
		//debug_stop();
	};
	//*******************************************************************************************//
	//								Вызов функции в указанной нити								 //
	//*******************************************************************************************//
	//Внутренняя функция. Непосредственная реализация здесь.
	void __exec_thread(thread* dst);
	void __exec_thread(thread* dst)
	{
		sp_temp = readSP();
		__operated = dst;							//После следующей операции локальные переменные
													//станут недоступны, так что переносим 
													//адрес потомка в глобальную переменную.
		PUSH_PROCESSOR_STATE_TO_STACK();			//Скидываем регистры в стек.
		__current -> stack_pointer = readSP();		//Устанавливаем в дескрипторе значение 
													//Stack Pointer
													//Теперь состояние нити соответствует спящему.
		copy_part_thread(__operated, __current, 
		PROC_STATE_SIZE + VOID_PTR_SIZE + 2);		//
		//copy_thread(__operated, __current);
		setSP(sp_temp);								//
	};
	
	//Оболочка функции копирования активной нити.
	//Пролог и эпилог, обеспечивают возврат различных значений.
	//Возвращает ноль для потомка, единицу для предка
	int exec_thread(thread* dst, void(* func)())
	{	
		thread* parent = __current;				//Запоминаем дескриптор родителя.		
		__exec_thread(dst);					    //Выполняем копирование активной нити.
		if (__current == parent) return 0;	//Сравниваем текущую активную нить с дескриптором родителя.
		else func();
		debug_panic("exec_thread return.");
	};
	
	int exec_thread_with_return(thread* dst, void(* func)())
	{	
		thread* parent = __current;				//Запоминаем дескриптор родителя.		
		__exec_thread(dst);					    //Выполняем копирование активной нити.
		if (__current == parent) return 0;	//Сравниваем текущую активную нить с дескриптором родителя.
		else func();
		change_thread(parent);
		debug_panic("exec_thread_with_return was invoked after return");
	};
	//*******************************************************************************************//
	//								Вызов функции в текущей нити								 //
	//*******************************************************************************************//
	//Сброс стека и запуск целевой функции. Запрет возврата.
	int exec_current_thread(void(* func)())
	{	
		drop_stack();
		func();
		debug_panic("exec_current_thread return.");
	};
	
	int exec_current_thread_nosafe(void(* func)())
	{
		//drop_stack();
		//long_goto(func);
		//TODO Need correct long_goto to use with pointer;
	};
	
	//*******************************************************************************************//
	//								Доступ к указателю активной нити							 //
	//*******************************************************************************************//
	thread* current_thread()
	{
	return __current;
	};