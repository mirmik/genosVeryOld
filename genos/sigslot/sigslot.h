#ifndef GENOS_SISLOT_H
	#define GENOS_SISLOT_H
	
	
	#include "genos/sigslot/delegate.h"	
	#include "genos/base_struct/monolist.h"	
	#include "genos/memory.h"	
	#include "genos/gstl/utility.h"	
	#include "genos/debug/debug.h"
	
	template<typename OutputType ,typename ... VarTypes>
	class listed_delegate
	{public:
		delegate<OutputType, VarTypes ... > 	dlg;
		monolist_head 							mlist;
	};
	
	
	
	template<typename OutputType ,typename ... VarTypes>
	class sigslot{
		public:
		monolist_head head;
		sigslot() : head(&head) {};
		
		void clear()
		{
			typedef listed_delegate<OutputType, VarTypes ... > ldlgtype;
			monolist_head * pos, *n ,*p;
			monolist_for_each_safe(p, pos, n, &head)
			{
				__list_del(p, n);
				sys_deallocate(monolist_entry(pos, ldlgtype , mlist));
			};
			
		};
		
		template <typename T>
		T operator()(VarTypes ... arg) volatile 
		{
		T res;
			listed_delegate<OutputType, VarTypes ... > * pos;
			monolist_for_each_entry(pos,&head,mlist)
			{
				res = pos->dlg(arg ...);
			};		
			return res;
		};
		
		
		
		void operator()(VarTypes ... arg) volatile 
		{
			listed_delegate<OutputType, VarTypes ... > * pos;
			monolist_for_each_entry(pos,&head,mlist)
			{
				pos->dlg(arg ...);
			};		
		};
		
				
		void include (OutputType(*func)(VarTypes ...))
		{
			listed_delegate<OutputType, VarTypes ... > *l 
			= genos::sys_allocate<listed_delegate<OutputType, VarTypes ... >>(1);
			l->dlg = func;
			listed_delegate<OutputType, VarTypes ... > * pos;
			monolist_last_entry(pos, &head, mlist);	
			monolist_add(&l->mlist, &pos->mlist);
		};
		
		
		void priority_include (OutputType(*func)(VarTypes ...))
		{
			listed_delegate<OutputType, VarTypes ... > *l 
			= genos::sys_allocate<listed_delegate<OutputType, VarTypes ... >>(1);
			l->dlg = func;
			monolist_add(&l->mlist, &head);
		};
		
		template <typename T1, typename T2>
		void include (T1* ptr_obj, OutputType(T2::*mtd)(VarTypes ...))
		{
			listed_delegate<OutputType, VarTypes ... > *l 
			= genos::sys_allocate<listed_delegate<OutputType, VarTypes ... >>(1);
			l->dlg = {ptr_obj, mtd};
			listed_delegate<OutputType, VarTypes ... > * pos;
			monolist_last_entry(pos, &head, mlist);	
			monolist_add(&l->mlist, &pos->mlist);
		};
		
		template <typename T1, typename T2>
		void priority_include (T1* ptr_obj, OutputType(T2::*mtd)(VarTypes ...))
		{
			listed_delegate<OutputType, VarTypes ... > *l 
			= genos::sys_allocate<listed_delegate<OutputType, VarTypes ... >>(1);
			l->dlg = {ptr_obj, mtd};
			monolist_add(&l->mlist, &head);
		};
		
		sigslot& operator+= (OutputType(*func)(VarTypes ...)) {include(func);return *this;};	
		
		template <typename T1, typename T2>
		sigslot& operator+= (std::pair<T1* , OutputType(T2::*)(VarTypes ...)> pr) 
		{include(pr.first, pr.second);return *this;};	
		
		
		template <typename T1>
		sigslot& operator+= (std::pair<T1* , delegate_mtd_t> pr) 
		{class AbstractDelegatedClass{};
			include(pr.first, 
			horrible_cast<OutputType(AbstractDelegatedClass::*)(VarTypes ...),delegate_mtd_t>
			(pr.second));
			return *this;};	
		
		
		
		sigslot& operator!= (OutputType(*func)(VarTypes ...)) {priority_include(func);return *this;};	
		
		template <typename T1, typename T2>
		sigslot& operator!= (std::pair<T1* , OutputType(T2::*)(VarTypes ...)> pr) 
		{priority_include(pr.first, pr.second);return *this;};	
		
		
		void drop(delegate<OutputType, VarTypes ... >  dlg)
		{
			typedef listed_delegate<OutputType, VarTypes ... > ldlgtype;
			monolist_head * pos, *n ,*p;
			ldlgtype* ptr;
			
			monolist_for_each_safe(p, pos, n, &head)
			{
				ptr = monolist_entry(pos, ldlgtype , mlist);
				if (dlg == ptr->dlg) 
				{
					__list_del(p, n);
					sys_deallocate(ptr);
					return;
					}
				else p = pos;
			};
		}
		
		sigslot& operator-= (OutputType(*func)(VarTypes ...)) 
		{drop(delegate<OutputType, VarTypes ...>(func));return *this;};	
		
		template <typename T1, typename T2>
			sigslot& operator-= (std::pair<T1* , OutputType(T2::*)(VarTypes ...)> pr) 
		{drop(delegate<OutputType, VarTypes ...> (pr));return *this;};	
		
	};
	
	
	
	
	
	
	
#endif