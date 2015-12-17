#ifndef DYNAMICRING_H
	#define DYNAMICRING_H
	
	#include "charqueue/queue.h"
	#include "charqueue/ring.h"
	
	#include <inttypes.h>
	
	//#include <stdio.h> // for size_t
	#include "platform.h" // for kmalloc
	#include "glist.h"
	
	struct ring_list
	{
		ring_t* ring;
		list_head list;
	};
	
	class dynamicring : public Queue_p
	{
		public:
		list_head ring_head;
		int quantum;
		int count;
		ring_list *tail, *head;
		dynamicring(int _quantum);
		void engage_ring();
		void absolve_ring();
		int peek(int n);
		int available();
		int push(char c);
		int pop();
	};
#endif