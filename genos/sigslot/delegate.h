#ifndef GENOS_DELEGATE
	#define GENOS_DELEGATE
	
	#include "genos/sigslot/horrible_cast.h"
	#include "genos/platform/delegate.h"	
	#include "genos/gstl/utility.h"	
	
	template<typename OutputType ,typename ... VarTypes>	
	class delegate
	{public:
		
		static constexpr uint8_t METHOD =0x01;
		static constexpr uint8_t FUNCTION =0x02;
		
		delegate_obj_t object;
		union {
			delegate_mtd_t method;
			delegate_fnc_t function;
		};
		uint8_t type;
		
		delegate() : object(0) , type(0) {(sizeof(method) >= sizeof(function)) ? method=0 : function=0;};
		
		template<typename T1, typename T2>
		delegate(T1* ptr_obj, OutputType(T2::*mtd)(VarTypes ...))  : function(0)
		{
			object = horrible_cast<delegate_obj_t, T1*>(ptr_obj);
			method = horrible_cast<delegate_mtd_t, OutputType(T2::*)(VarTypes ...)>(mtd);
			type = METHOD;
		};	
		
		template<typename T1, typename T2>
		delegate(const std::pair<T1* , OutputType(T2::*)(VarTypes ...)>& pr)  : function(0)
		{
			object = horrible_cast<delegate_obj_t, T1*>(pr.first);
			method = horrible_cast<delegate_mtd_t, OutputType(T2::*)(VarTypes ...)>(pr.second);
			type = METHOD;
		};	
		
		template<typename T1, typename T2>
		delegate(std::pair<T1* , delegate_mtd_t> pr)  : function(0)
		{
			object = horrible_cast<delegate_obj_t, T1*>(pr.first);
			method = pr.second;
			type = METHOD;
		};			
		
		delegate(OutputType(*func)(VarTypes ...)) : object(0) , method(0)
		{
			function = horrible_cast<delegate_fnc_t, OutputType(*)(VarTypes ...)>(func);
			type = FUNCTION;
		};	
		
		
		inline OutputType method_invoke(VarTypes ... arg)
		{
			class AbstractDelegatedClass{};
			auto obj = horrible_cast<AbstractDelegatedClass*, delegate_obj_t>(object);
			auto mtd = horrible_cast<OutputType(AbstractDelegatedClass::*)(VarTypes ...),delegate_mtd_t>(method);
			return (obj->*mtd)(arg ...);
		};
		
		inline OutputType function_invoke(VarTypes ... arg)
		{
			auto func = horrible_cast<OutputType(*)(VarTypes ...),delegate_fnc_t>(function);
			return (func)(arg ...);
		};
		
		OutputType operator()(VarTypes ... arg) {
			switch (type)
			{
				case METHOD: 
				return method_invoke(arg ...);
				
				case FUNCTION: 
				return function_invoke(arg ...);
				
			};
		};
		
		bool operator==(delegate<OutputType ,VarTypes ... > b)
		{return (method==b.method && function==b.function && object==b.object) ? true : false;};
	};	
	
	#define method(obj, mtd) std::make_pair(&obj, &mtd)
	
#endif