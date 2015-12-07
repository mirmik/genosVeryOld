
//2012-2015 Mirmik 
//���������� ������� ���������� ��������� ����������.
//�������������� �� AVR2560

//#pragma GCC optimize "-O0"
#include "genos/debug/debug.h"
#include "genos/subst/subst.h"

	thread* __current;			//��������� �� �������� ����.
	//��� ����������� �������������:
	size_t sp_temp;
	thread* __operated;			//��������� �� ���� ������������ ������� ����������� ��������.
	
	
	//*******************************************************************************************//
	//									�������� ���������										 //
	//*******************************************************************************************//
	//Black magic
	
	void substitution ()__attribute__((__noinline__));
	void substitution () 				//������� �������. ������ ��������.
	{											//��� ������ � __operated ������ ����  
												//����� ������������ ����.
		PUSH_PROCESSOR_STATE_TO_STACK();		//��������� �������� � ����.
		__current -> stack_pointer = readSP();	//��������� ��������� �����.
		__current = __operated;					//������� ���������� �������� ����.
		setSP(__current -> stack_pointer);		//��������� ��������� �����.
		POP_PROCESSOR_STATE_FROM_STACK();		//��������� �������� �� �����.
	};
	
	
	//*******************************************************************************************//
	//								����� ����� ����										 //
	//*******************************************************************************************//
	void change_thread(thread* thr)		//�������� ��� substitution
	{									//�������������� � �������� �������������.
		__operated = thr;
		substitution();
	};
	
	//*******************************************************************************************//
	//								������������� �������� ����									 //
	//*******************************************************************************************//
	void init_current_thread(thread* thr, size_t stcktop)
	{	
		__current = thr;						//���������� this � �������� �����
		set_stack_thread(thr, stcktop);		//��������� stack_top
	};
	
	
	void set_stack_thread(thread* thr, size_t stcktop)
	{
		thr -> stack_top      = stcktop;
		thr -> stack_pointer  = stcktop;
		};
	
	//*******************************************************************************************//
	//								����������� ��������� ����									 //
	//*******************************************************************************************//
	void copy_thread(thread* dst, thread* src)
	{		
		
		//������ ������� ��� �������� �����������.
		uint8_t* begin = 	(uint8_t*)src->stack_top + 1;
		uint8_t* end =	 	(uint8_t*)src->stack_pointer;
		
		uint8_t* dst_ptr = 	(uint8_t*)dst->stack_top + 1;
		uint8_t* src_ptr = begin;
		
		//�������� ���������� ����� ��������� � ����� ����.
		for(; src_ptr != end ;) *--dst_ptr = *--src_ptr;
		
		//��� ����� ��������� stack_pointer ������������������� ��������.
		dst->stack_pointer = dst->stack_top - (begin - end - 1);
		
		//debug_print_dump((void*)dst->stack_pointer, dst->stack_top - dst->stack_pointer);
		//debug_print_dump((void*)src->stack_pointer, src->stack_top - src->stack_pointer);
		//debug_stop();
	};
	//*******************************************************************************************//
	//								����������� ��������� ������� ����							 //
	//*******************************************************************************************//
	//���������� �������. ���������������� ���������� �����.
	void __fork_thread(thread* dst)__attribute__((noinline));
	void __fork_thread(thread* dst)
	{	
		sp_temp = readSP();
		__operated = dst;							//����� ��������� �������� ��������� ����������
													//������ ����������, ��� ��� ��������� 
													//����� ������� � ���������� ����������.
		PUSH_PROCESSOR_STATE_TO_STACK();			//��������� �������� � ����.
		__current -> stack_pointer = readSP();		//������������� � ����������� �������� 
													//Stack Pointer
													//������ ��������� ���� ������������� �������.
		copy_thread(__operated, __current);		//�������� ��������� ���� � ���� �������.
		setSP(sp_temp);							//���������� ��������� ���������� � ���������.
		//POP_PROCESSOR_STATE_FROM_STACK();
	};
	
	//�������� ������� ����������� �������� ����.
	//������ � ������, ������������ ������� ��������� ��������.
	//���������� ���� ��� �������, ������� ��� ������
	int fork_thread(thread* dst)
	{	
		thread* parent = __current;				//���������� ���������� ��������.		
		__fork_thread(dst);					    //��������� ����������� �������� ����.
		return (__current == parent ? 1 : 0);	//���������� ������� �������� ���� � ������������ ��������.
	};
	
	
	
	//*******************************************************************************************//
	//								����������� ����� �����										 //
	//*******************************************************************************************//
	void copy_part_thread(thread* dst, thread* src, size_t copy_count);
	void copy_part_thread(thread* dst, thread* src, size_t copy_count)
	{		
		//������ ������� ��� �������� �����������.
		uint8_t* begin = 	(uint8_t*)src->stack_pointer + copy_count + 1;
		uint8_t* end =	 	(uint8_t*)src->stack_pointer;
		
		uint8_t* dst_ptr = 	(uint8_t*)dst->stack_top + 1;
		uint8_t* src_ptr = begin;
		
		//�������� ���������� ����� ��������� � ����� ����.
		for(; src_ptr != end ;) *--dst_ptr = *--src_ptr;
		
		//��� ����� ��������� stack_pointer ������������������� ��������.
		dst->stack_pointer = dst->stack_top - (begin - end - 1);
		//debug_print_dump((void*)dst->stack_pointer, dst->stack_top - dst->stack_pointer);
		//debug_print_dump((void*)src->stack_pointer, src->stack_top - src->stack_pointer);
		//debug_printhex_uint16((uint16_t)(exec_thread));dln;
		//debug_printhex_uint16((uint16_t)(__exec_thread));dln;
		//debug_stop();
	};
	//*******************************************************************************************//
	//								����� ������� � ��������� ����								 //
	//*******************************************************************************************//
	//���������� �������. ���������������� ���������� �����.
	void __exec_thread(thread* dst);
	void __exec_thread(thread* dst)
	{
		sp_temp = readSP();
		__operated = dst;							//����� ��������� �������� ��������� ����������
													//������ ����������, ��� ��� ��������� 
													//����� ������� � ���������� ����������.
		PUSH_PROCESSOR_STATE_TO_STACK();			//��������� �������� � ����.
		__current -> stack_pointer = readSP();		//������������� � ����������� �������� 
													//Stack Pointer
													//������ ��������� ���� ������������� �������.
		copy_part_thread(__operated, __current, 
		PROC_STATE_SIZE + VOID_PTR_SIZE + 2);		//
		//copy_thread(__operated, __current);
		setSP(sp_temp);								//
	};
	
	//�������� ������� ����������� �������� ����.
	//������ � ������, ������������ ������� ��������� ��������.
	//���������� ���� ��� �������, ������� ��� ������
	int exec_thread(thread* dst, void(* func)())
	{	
		thread* parent = __current;				//���������� ���������� ��������.		
		__exec_thread(dst);					    //��������� ����������� �������� ����.
		if (__current == parent) return 0;	//���������� ������� �������� ���� � ������������ ��������.
		else func();
		debug_panic("exec_thread return.");
	};
	
	int exec_thread_with_return(thread* dst, void(* func)())
	{	
		thread* parent = __current;				//���������� ���������� ��������.		
		__exec_thread(dst);					    //��������� ����������� �������� ����.
		if (__current == parent) return 0;	//���������� ������� �������� ���� � ������������ ��������.
		else func();
		change_thread(parent);
		debug_panic("exec_thread_with_return was invoked after return");
	};
	//*******************************************************************************************//
	//								����� ������� � ������� ����								 //
	//*******************************************************************************************//
	//����� ����� � ������ ������� �������. ������ ��������.
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
	//								������ � ��������� �������� ����							 //
	//*******************************************************************************************//
	thread* current_thread()
	{
	return __current;
	};