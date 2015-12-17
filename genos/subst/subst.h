

//2012-2015 Mirmik 

#ifndef GENOS_SUBST_SCHEDULER
	#define GENOS_SUBST_SCHEDULER
	
	//#include "inttypes.h"
	//#include "string.h"
	#include "genos/types.h"
	#include <genos/platform/subst.h>
			
		//Дескриптор нити.
		struct _thread 
		{
			volatile size_t stack_pointer;	//Поле для сохранения указателя стека.
			volatile size_t stack_top;		//Вершина стека.		
		};
		typedef struct _thread thread;
extern "C" {		
		//Настроить нить как текущую.
		void init_current_thread(thread* thr, size_t ptr);
		
		//Инициализация стека.
		void set_stack_thread(thread* thr, size_t ptr);
				
		//Вызов смены нити.
		void change_thread(thread* thr);
				
		//Функция копирует состояние нити из src в dst
		//void copy_thread(thread* dst, thread* src);
		
		//Функция копирует состояние текущей нити в inited.
		//Возвращает 1 для родительской нити и 0 для inited нити.
		int fork_thread(thread* inited);
		
		//Функция обнуляет состояние нити inited и запускает в ней ф-ю func.
		//При возврате выдаёт системную ошибку
		int exec_thread(thread* inited, void(* func)());
		
		//Функция обнуляет состояние нити inited и запускает в ней ф-ю func.
		//При возврате возвращает управление создавшей его нити.
		int exec_thread_with_return(thread* inited, void(* func)());
		
		//Возвращает адрес дескриптора активной нити.
		thread* current_thread();
		
		//Указатель на активную нить. 
		//Раскомментировать для прямого использования.
		//extern thread* __current;
	
		int exec_current_thread(void(* func)());
	
		//drop_stack defined in platform/subst.h
		//long_goto defined in platform/subst.h
};	
#endif