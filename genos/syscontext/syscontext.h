#ifndef  GENOS_SYSCONTEXT_H
	#define GENOS_SYSCONTEXT_H
	
	#include "genos/iostream/iostream.h"
	#include "genos/defs.h"
	
	//��������� ���������� � �������� ���������.
	struct syscontext
	{
		//������ �����-������
		#ifdef SYSCONTEXT_IOSTREAM
		genos::ostream __cout;
		genos::istream __cin;
		#endif
		
		//Extended return.
		//����� �������������� ��� �������� ������� ����������.
		int extreturn = 0;
	};
	
	//"������" ���������� ����������.
	//���������� ���������, �� �� �����������:
	//��� ������ � ����������, ��� ��� ��� ��� ����������� ���������.
	extern bool __subst;
	
	extern syscontext current_syscontext ;
	
	#define cout 	current_syscontext.__cout
	#define cin 	current_syscontext.__cin
	#define cerr 	current_syscontext.__cerr
	
	#define extret 	current_syscontext.extreturn
	
	#define CAN_SUBST 	__subst
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
#endif