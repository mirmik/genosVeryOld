#ifndef MTIMER_H
	#define MTIMER_H
	
	#include "genos/platform.h"
	#include "genos/time/basic_timer.h"
	
	
	namespace genos{
		
		class mtimer : public basic_timer
		{
			typedef unsigned long time_t;
					
			public:
			uint8_t status;
			mtimer() {};      
			
			//Простой старт. Таймер сработает через _interval миллисекунд, после вызова этой функции.
			void set(time_t _interval)                {_set(millis(), _interval);status=1;};
			
			//Вариант функции set с явной установкой точки отсчета. Использовать для синхронного старта группы таймеров.
			void set(time_t _start, time_t _interval) {_set(_start, _interval);status=1;};
			
			//После вызова функции set_bias таймер сработает через _interval миллискунд после предыдущего срабатывания таймера. 
			void set_bias(time_t _interval) {_set(s + i, _interval);status=1;};
			
			//Функция проверки состояния таймера. Может дать положительное значение только один раз на каждую установку.
			bool check() {
				if (!status) return false;
				else
				{
					bool b = _check(millis());
					if (b) status=0;
					return b;
				};
				
			};
			bool operator()(){return check();};
			
		};
	};
#endif					