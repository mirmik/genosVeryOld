#ifndef ITERATION_COUNTER_H
	#define ITERATION_COUNTER_H
	//������� �������� ����������. by Mirmik
	
	#include "genos/debug/helper_macro.h"
	#include "genos/debug/debug_macro.h"
	
	
	
	//��������� ����������.
	#define do_once \
    debug_place(); static int _var_generate(0) = 1; \
    if (_var_generate(0)) if (_var_generate(0)--) 
	
	//��������� b ��������.
	#define do_iteration(b) \
    debug_place(); static int _var_generate(0) = 0; \
    if (_var_generate(0) < b) if (++_var_generate(0)) 
	
	//��������� ����� b �������� (��������������).
	#define do_iteration_after(b) \
	debug_place(); static int _var_generate(0) = 0; \
	if (_var_generate(0) < b) ++_var_generate(0); else
	
	//��������� �� a �������� �� b �������� (a ������������, b ��������������).
	#define do_iteration_between(a, b) \
	debug_place(); static int _var_generate(0) = 0; \
	if (_var_generate(0) < a) ++_var_generate(0); else \
	if (_var_generate(0) < b) if (++_var_generate(0))
	
	//��������� ����� only_once, do_iteration, do_between_iteration
	#define do_after else;else
	
	
	//��������� ������� ����������.
	struct iteration_counter
	{
		long long iteration;
		long long helper;
	};
	
	#define iter_start(obj) \
	static iteration_counter obj = {0, 0}; \
	obj.iteration++;\
	switch(obj.helper){case 0:
	
	//
	#define iter(obj,a) if (obj.iteration == a) obj.helper = a; break; case a:
	
	//���������� ����������.
	#define iter_end(obj,a) if (obj.iteration == a) obj.helper = a; break; default: break; }
	
	//����������������� ����������.
	#define iter_end_unstoped(obj) if (obj.iteration >= obj.helper) obj.iteration = obj.helper; break;}
	
	//������ �������������.
	//iter_start(obj)     do_something0();	//��������� �� ������ �������� 
	//iter(obj,2)         do_something1();	//��������� �� ������ �� ��������� ��������
	//iter(obj,4)         do_something2();	//��������� � ��������� �� ������� ��������
	//iter_end(obj,10); 
	
	
	
#endif