#ifndef GENOS_LINUX_LIST_BASIC
	#define GENOS_LINUX_LIST_BASIC
	
	#include "genos/debug/debug.h"
	#include "genos/base_struct/base_struct_def.h"
	
	#define LIST_POISON1 ((list_head*)-1)
	#define LIST_POISON2 ((list_head*)-2)
	
	
	
	class list_head{			
		public:
		list_head* next;
		list_head* prev;
		
		list_head() : next(this), prev(this) {};
		list_head(list_head* _next, list_head* _prev) : next(_next), prev(_prev) {}; 
	};
	
	static inline void INIT_LIST_HEAD(struct list_head *list)
	{
		list->next = list;
		list->prev = list;
	}
	
	#define LIST_HEAD_INIT(name) { &(name), &(name) }
	
	#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)
	
	
	#ifndef container_of
		#define container_of(ptr, type, member) ({              \
		const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
		(type *)( (char *)__mptr - offsetof(type,member) );})
	#endif
	
	/*
		* Simple doubly linked list implementation.
		*
		* Some of the internal functions ("__xxx") are useful when
		* manipulating whole lists rather than single entries, as
		* sometimes we already know the next/prev entries and we can
		* generate better code by using them directly rather than
		* using the generic single-entry routines.
	*/
	
	
	
	/*
		* Insert a _new entry between two known consecutive entries.
		*
		* This is only for internal list manipulation where we know
		* the prev/next entries already!
	*/
	//Добавляет элемент _new между двумя последовательно расположенными элементами.
	//Только для внутреннего использования, когда известны prev/next элементы. 
	static inline void __list_add(struct list_head *_new,
	struct list_head *prev,
	struct list_head *next)
	{
		next->prev = _new;
		_new->next = next;
		_new->prev = prev;
		prev->next = _new;
	}
	
	
	/**
		* list_add - add a _new entry
		* @_new: _new entry to be added
		* @head: list head to add it after
		*
		* Insert a _new entry after the specified head.
		* This is good for implementing stacks.
	*/
	//Добавить _new элемент после head.
	//Применяется для добавления в стэк.
	static inline void list_add(struct list_head *_new, struct list_head *head)
	{
		__list_add(_new, head, head->next);
	}
	
	
	/**
		* list_add_tail - add a _new entry
		* @_new: _new entry to be added
		* @head: list head to add it before
		*
		* Insert a _new entry before the specified head.
		* This is useful for implementing queues.
	*/
	//Добавить _new элемент перед head.
	//Применяется для добавления в очередь.
	static inline void list_add_tail(struct list_head *_new, struct list_head *head)
	{
		__list_add(_new, head->prev, head);
	}
	
	/*
		* Delete a list entry by making the prev/next entries
		* point to each other.
		*
		* This is only for internal list manipulation where we know
		* the prev/next entries already!
	*/
	//Удаляет элемент находящийся между prev/next элементами.
	//Только для внутреннего использования, когда известны prev/next элементы. 
	static inline void __list_del(struct list_head * prev, struct list_head * next)
	{
		next->prev = prev;
		prev->next = next;
	}
	
	/**
		* list_del - deletes entry from list.
		* @entry: the element to delete from the list.
		* Note: list_empty() on entry does not return true after this, the entry is
		* in an undefined state.
	*/
	//Удаляет entry из списка.
	//entry остаётся в неопределенном состоянии.
	static inline void __list_del_entry(struct list_head *entry)
	{
		__list_del(entry->prev, entry->next);
	}
	
	static inline void list_del(struct list_head *entry)
	{
		__list_del(entry->prev, entry->next);
		entry->next = LIST_POISON1;
		entry->prev = LIST_POISON2;
	}
	
	
	/**
		* list_replace - replace old entry by _new one
		* @old : the element to be replaced
		* @_new : the _new element to insert
		*
		* If @old was empty, it will be overwritten.
	*/
	//Заменяет элемент old в списке на элемент new.
	//entry остаётся в неопределенном состоянии.
	static inline void list_replace(struct list_head *old,
	struct list_head *_new)
	{
		_new->next = old->next;
		_new->next->prev = _new;
		_new->prev = old->prev;
		_new->prev->next = _new;
	}
	
	static inline void list_replace_init(struct list_head *old,
	struct list_head *_new)
	{
		list_replace(old, _new);
		INIT_LIST_HEAD(old);
	}
	
	/**
		* list_del_init - deletes entry from list and reinitialize it.
		* @entry: the element to delete from the list.
	*/
	//Удаляет entry и реинициализирует его.
	static inline void list_del_init(struct list_head *entry)
	{
		__list_del_entry(entry);
		INIT_LIST_HEAD(entry);
	}
	
	/**
		* list_move - delete from one list and add as another's head
		* @list: the entry to move
		* @head: the head that will precede our entry
	*/
	//Удаляет элемент из одного списка и добавляя в другой
	//после элемента head.
	static inline void list_move(struct list_head *list, struct list_head *head)
	{
		__list_del_entry(list);
		list_add(list, head);
	}
	
	/**
		* list_move_tail - delete from one list and add as another's tail
		* @list: the entry to move
		* @head: the head that will follow our entry
	*/
	//Удаляет элемент из одного списка и добавляя в другой
	//перед элементом head.
	static inline void list_move_tail(struct list_head *list,
	struct list_head *head)
	{
		__list_del_entry(list);
		list_add_tail(list, head);
	}
	
	/**
		* list_is_last - tests whether @list is the last entry in list @head
		* @list: the entry to test
		* @head: the head of the list
	*/
	//Проверяет, является ли list последним в списке.
	static inline int list_is_last(const struct list_head *list,
	const struct list_head *head)
	{
		return list->next == head;
	}
	
	/**
		* list_empty - tests whether a list is empty
		* @head: the list to test.
	*/
	//Проверяет, является ли head пустым списком.
	static inline int list_empty(const struct list_head *head)
	{
		return head->next == head;
	}
	
	
	
	/**
		* list_empty_careful - tests whether a list is empty and not being modified
		* @head: the list to test
		*
		* Description:
		* tests whether a list is empty _and_ checks that no other CPU might be
		* in the process of modifying either member (next or prev)
		*
		* NOTE: using list_empty_careful() without synchronization
		* can only be safe if the only activity that can happen
		* to the list entry is list_del_init(). Eg. it cannot be used
		* if another CPU could re-list_add() it.
	*/ 
	//Проверяет, является ли head пустым списком.
	//Также убеждается в его коректности.
	static inline int list_empty_careful(const struct list_head *head)
	{
		struct list_head *next = head->next;
		return (next == head) && (next == head->prev);
	}
	
	/**
		* list_rotate_left - rotate the list to the left
		* @head: the head of the list
	*/
	//Проворачивает список на один элемент.
	//Первый становится последним.
	static inline void list_rotate_left(struct list_head *head)
	{
		struct list_head *first;
		
		if (!list_empty(head)) {
			first = head->next;
			list_move_tail(first, head);
		}
	}
	
	/**
		* list_is_singular - tests whether a list has just one entry.
		* @head: the list to test.
	*/
	//Возвращает истину, если в списке остался только один элемент.
	static inline int list_is_singular(const struct list_head *head)
	{
		return !list_empty(head) && (head->next == head->prev);
	}
	
	static inline void __list_cut_position(struct list_head *list,
	struct list_head *head, struct list_head *entry)
	{
		struct list_head *new_first = entry->next;
		list->next = head->next;
		list->next->prev = list;
		list->prev = entry;
		entry->next = list;
		head->next = new_first;
		new_first->prev = head;
	}
	
	
	//Вырезает часть листа между head и entry(послений - включительно)
	//list становится новым заголовком вырезанной части. 
	//Предыдущее его состояние теряется.
	/**
		* list_cut_position - cut a list into two
		* @list: a _new list to add all removed entries
		* @head: a list with entries
		* @entry: an entry within head, could be the head itself
		*	and if so we won't cut the list
		*
		* This helper moves the initial part of @head, up to and
		* including @entry, from @head to @list. You should
		* pass on @entry an element you know is on @head. @list
		* should be an empty list or a list you do not care about
		* losing its data.
		*
	*/
	static inline void list_cut_position(struct list_head *list,
	struct list_head *head, struct list_head *entry)
	{
		if (list_empty(head))
		return;
		if (list_is_singular(head) &&
		(head->next != entry && head != entry))
		return;
		if (entry == head)
		INIT_LIST_HEAD(list);
		else
		__list_cut_position(list, head, entry);
	}
	
	static inline void __list_splice(const struct list_head *list,
	struct list_head *prev,
	struct list_head *next)
	{
		struct list_head *first = list->next;
		struct list_head *last = list->prev;
		
		first->prev = prev;
		prev->next = first;
		
		last->next = next;
		next->prev = last;
	}
	
	/**
		* list_splice - join two lists, this is designed for stacks
		* @list: the _new list to add.
		* @head: the place to add it in the first list.
	*/
	//Соединяет два списка. Содержимое списка list оказывается  
	// в начале списка head
	static inline void list_splice(const struct list_head *list,
	struct list_head *head)
	{
		if (!list_empty(list))
		__list_splice(list, head, head->next);
	}
	
	/**
		* list_splice_tail - join two lists, each list being a queue
		* @list: the _new list to add.
		* @head: the place to add it in the first list.
	*/
	//Соединяет два списка. Содержимое списка list оказывается  
	// в хвосте списка head
	static inline void list_splice_tail(struct list_head *list,
	struct list_head *head)
	{
		if (!list_empty(list))
		__list_splice(list, head->prev, head);
	}
	
	/**
		* list_splice_init - join two lists and reinitialise the emptied list.
		* @list: the _new list to add.
		* @head: the place to add it in the first list.
		*
		* The list at @list is reinitialised
	*/
	//Соединяет два списка. Содержимое списка list оказывается  
	// в начале списка head. Реинициализирует элемент list
	static inline void list_splice_init(struct list_head *list,
	struct list_head *head)
	{
		if (!list_empty(list)) {
			__list_splice(list, head, head->next);
			INIT_LIST_HEAD(list);
		}
	}
	
	/**
		* list_splice_tail_init - join two lists and reinitialise the emptied list
		* @list: the _new list to add.
		* @head: the place to add it in the first list.
		*
		* Each of the lists is a queue.
		* The list at @list is reinitialised
	*/
	//Соединяет два списка. Содержимое списка list оказывается  
	// в хвосте списка head. Реинициализирует элемент list
	static inline void list_splice_tail_init(struct list_head *list,
	struct list_head *head)
	{
		if (!list_empty(list)) {
			__list_splice(list, head->prev, head);
			INIT_LIST_HEAD(list);
		}
	}
	
	/**
		* list_entry - get the struct for this entry
		* @ptr:	the &struct list_head pointer.
		* @type:	the type of the struct this is embedded in.
		* @member:	the name of the list_head within the struct.
	*/
	//Расчитывает структуру, содержащую элемент списка ptr.
	#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)
	
	/**
		* list_first_entry - get the first element from a list
		* @ptr:	the list head to take the element from.
		* @type:	the type of the struct this is embedded in.
		* @member:	the name of the list_head within the struct.
		*
		* Note, that list is expected to be not empty.
	*/
	//Расчитывает первую структуру, содержащуюся в списке ptr,
	//или структуру, содержащую элемент списка следующий за ptr.
	//лист не должен быть пустым.
	#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)
	
	/**
		* list_last_entry - get the last element from a list
		* @ptr:	the list head to take the element from.
		* @type:	the type of the struct this is embedded in.
		* @member:	the name of the list_head within the struct.
		*
		* Note, that list is expected to be not empty.
	*/
	//Расчитывает последнюю структуру, содержащуюся в списке ptr,
	//или структуру, содержащую элемент списка предшествующий ptr.
	//лист не должен быть пустым.
	#define list_last_entry(ptr, type, member) \
	list_entry((ptr)->prev, type, member)
	
	/**
		* list_first_entry_or_null - get the first element from a list
		* @ptr:	the list head to take the element from.
		* @type:	the type of the struct this is embedded in.
		* @member:	the name of the list_head within the struct.
		*
		* Note that if the list is empty, it returns NULL.
	*/
	//Расчитывает первую структуру, содержащуюся в списке ptr.
	//возвращает NULL, если список пустой.
	#define list_first_entry_or_null(ptr, type, member) \
	(!list_empty(ptr) ? list_first_entry(ptr, type, member) : NULL)
	
	/**
		* list_next_entry - get the next element in list
		* @pos:	the type * to cursor
		* @member:	the name of the list_head within the struct.
	*/
	//Расчитывает следующую структуру.
	#define list_next_entry(pos, member) \
	list_entry((pos)->member.next, typeof(*(pos)), member)
	
	/**
		* list_prev_entry - get the prev element in list
		* @pos:	the type * to cursor
		* @member:	the name of the list_head within the struct.
	*/
	//Расчитывает предыдущую структуру.
	#define list_prev_entry(pos, member) \
	list_entry((pos)->member.prev, typeof(*(pos)), member)
	
	/**
		* list_for_each	-	iterate over a list
		* @pos:	the &struct list_head to use as a loop cursor.
		* @head:	the head for your list.
	*/
	//Цикл, выполняющийся по всем элементам списка.
	#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)
	
	/**
		* list_for_each_prev	-	iterate over a list backwards
		* @pos:	the &struct list_head to use as a loop cursor.
		* @head:	the head for your list.
	*/
	//Цикл, выполняющийся по всем элементам списка в обратном
	//направлении
	#define list_for_each_prev(pos, head) \
	for (pos = (head)->prev; pos != (head); pos = pos->prev)
	
	/**
		* list_for_each_safe - iterate over a list safe against removal of list entry
		* @pos:	the &struct list_head to use as a loop cursor.
		* @n:		another &struct list_head to use as temporary storage
		* @head:	the head for your list.
	*/
	//Цикл, выполняющийся по всем элементам списка.
	//Безопасен при использовании операций удаления.
	#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
	pos = n, n = pos->next)
	
	/**
		* list_for_each_prev_safe - iterate over a list backwards safe against removal of list entry
		* @pos:	the &struct list_head to use as a loop cursor.
		* @n:		another &struct list_head to use as temporary storage
		* @head:	the head for your list.
	*/
	//Цикл, выполняющийся по всем элементам списка в обратном
	//направлении
	//Безопасен при использовании операций удаления.
	#define list_for_each_prev_safe(pos, n, head) \
	for (pos = (head)->prev, n = pos->prev; \
	pos != (head); \
	pos = n, n = pos->prev)
	
	/**
		* list_for_each_entry	-	iterate over list of given type
		* @pos:	the type * to use as a loop cursor.
		* @head:	the head for your list.
		* @member:	the name of the list_head within the struct.
	*/
	//Цикл, выполняющийся по всем структурам списка.
	#define list_for_each_entry(pos, head, member)				\
	for (pos = list_first_entry(head, typeof(*pos), member);	\
	&pos->member != (head);					\
	pos = list_next_entry(pos, member))
	
	/**
		* list_for_each_entry_reverse - iterate backwards over list of given type.
		* @pos:	the type * to use as a loop cursor.
		* @head:	the head for your list.
		* @member:	the name of the list_head within the struct.
	*/
	//Цикл, выполняющийся по всем структурам списка, движущийся в
	//обратном направлении.
	#define list_for_each_entry_reverse(pos, head, member)			\
	for (pos = list_last_entry(head, typeof(*pos), member);		\
	&pos->member != (head); 					\
	pos = list_prev_entry(pos, member))
	
	/**
		* list_prepare_entry - prepare a pos entry for use in list_for_each_entry_continue()
		* @pos:	the type * to use as a start point
		* @head:	the head of the list
		* @member:	the name of the list_head within the struct.
		*
		* Prepares a pos entry for use as a start point in list_for_each_entry_continue().
	*/
	//Подготавливает pos для использования в качестве курсора  list_for_each_entry_continue
	#define list_prepare_entry(pos, head, member) \
	((pos) ? : list_entry(head, typeof(*pos), member))
	
	/**
		* list_for_each_entry_continue - continue iteration over list of given type
		* @pos:	the type * to use as a loop cursor.
		* @head:	the head for your list.
		* @member:	the name of the list_head within the struct.
		*
		* Continue to iterate over list of given type, continuing after
		* the current position.
	*/
	//выполнять цикл, начиная со следующего элемента.
	#define list_for_each_entry_continue(pos, head, member) 		\
	for (pos = list_next_entry(pos, member);			\
	&pos->member != (head);					\
	pos = list_next_entry(pos, member))
	
	/**
		* list_for_each_entry_continue_reverse - iterate backwards from the given point
		* @pos:	the type * to use as a loop cursor.
		* @head:	the head for your list.
		* @member:	the name of the list_head within the struct.
		*
		* Start to iterate over list of given type backwards, continuing after
		* the current position.
	*/
	//выполнять цикл, начиная с предыдущего элемента в обратном направлении. 
	#define list_for_each_entry_continue_reverse(pos, head, member)		\
	for (pos = list_prev_entry(pos, member);			\
	&pos->member != (head);					\
	pos = list_prev_entry(pos, member))
	
	/**
		* list_for_each_entry_from - iterate over list of given type from the current point
		* @pos:	the type * to use as a loop cursor.
		* @head:	the head for your list.
		* @member:	the name of the list_head within the struct.
		*
		* Iterate over list of given type, continuing from current position.
	*/
	//Начать с этой точки.
	#define list_for_each_entry_from(pos, head, member) 			\
	for (; &pos->member != (head);					\
	pos = list_next_entry(pos, member))
	#define list_for_each_entry_continue(pos, head, member) 		
	/**
		* list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
		* @pos:	the type * to use as a loop cursor.
		* @n:		another type * to use as temporary storage
		* @head:	the head for your list.
		* @member:	the name of the list_head within the struct.
	*/
	//Стоек к удалению.
	#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_first_entry(head, typeof(*pos), member),	\
	n = list_next_entry(pos, member);			\
	&pos->member != (head); 					\
	pos = n, n = list_next_entry(n, member))
	
	/**
		* list_for_each_entry_safe_continue - continue list iteration safe against removal
		* @pos:	the type * to use as a loop cursor.
		* @n:		another type * to use as temporary storage
		* @head:	the head for your list.
		* @member:	the name of the list_head within the struct.
		*
		* Iterate over list of given type, continuing after current point,
		* safe against removal of list entry.
	*/
	//Стоек к удалению, начинает со следующей позиции.
	#define list_for_each_entry_safe_continue(pos, n, head, member) 		\
	for (pos = list_next_entry(pos, member), 				\
	n = list_next_entry(pos, member);				\
	&pos->member != (head);						\
	pos = n, n = list_next_entry(n, member))
	
	/**
		* list_for_each_entry_safe_from - iterate over list from current point safe against removal
		* @pos:	the type * to use as a loop cursor.
		* @n:		another type * to use as temporary storage
		* @head:	the head for your list.
		* @member:	the name of the list_head within the struct.
		*
		* Iterate over list of given type from current point, safe against
		* removal of list entry.
	*/
	#define list_for_each_entry_safe_from(pos, n, head, member) 			\
	for (n = list_next_entry(pos, member);					\
	&pos->member != (head);						\
	pos = n, n = list_next_entry(n, member))
	
	/**
		* list_for_each_entry_safe_reverse - iterate backwards over list safe against removal
		* @pos:	the type * to use as a loop cursor.
		* @n:		another type * to use as temporary storage
		* @head:	the head for your list.
		* @member:	the name of the list_head within the struct.
		*
		* Iterate backwards over list of given type, safe against removal
		* of list entry.
	*/
	#define list_for_each_entry_safe_reverse(pos, n, head, member)		\
	for (pos = list_last_entry(head, typeof(*pos), member),		\
	n = list_prev_entry(pos, member);			\
	&pos->member != (head); 					\
	pos = n, n = list_prev_entry(n, member))
	
	/**
		* list_safe_reset_next - reset a stale list_for_each_entry_safe loop
		* @pos:	the loop cursor used in the list_for_each_entry_safe loop
		* @n:		temporary storage used in list_for_each_entry_safe
		* @member:	the name of the list_head within the struct.
		*
		* list_safe_reset_next is not safe to use in general if the list may be
		* modified concurrently (eg. the lock is dropped in the loop body). An
		* exception to this is if the cursor element (pos) is pinned in the list,
		* and list_safe_reset_next is called after re-taking the lock and before
		* completing the current iteration of the loop body.
	*/
	#define list_safe_reset_next(pos, n, member)				\
	n = list_next_entry(pos, member)
	
	void static inline list_check(list_head* list, int m =20)
	{
		dpr("list_check:\n");
		int n;
		list_head* tmp = list;
		for (n=0;n < m; n++)
		{
			if ((size_t)list < 0x50) {debug_panic("list_next_zero\n");}; 
			if ((size_t)list > RAMEND - 0x50) {debug_panic("list_next_RAMEND\n");};
			debug_printhex_ptr(list->prev);dpc(':');
			debug_printhex_ptr(list);dpc(':');
			debug_printhex_ptr(list->next);dpc(':');
			dln;
			list = list -> next;
			if (list == tmp) {dpr("list_next_correct\n");goto stage2;}; 		
		};
		debug_panic("list_next_count is over\n");
		stage2:
		list = tmp;
		for (n=0;n < m; n++)
		{
			if ((size_t)list < 0x50) {debug_panic("list_prev_zero\n");};
			if ((size_t)list > RAMEND - 0x50) {debug_panic("list_prev_RAMEND\n");};
			debug_printhex_ptr(list->prev);dpc(':');
			debug_printhex_ptr(list);dpc(':');
			debug_printhex_ptr(list->next);dpc(':');
			dln;
			list = list -> prev;
			if (list == tmp) {dpr("list_prev_correct\n");goto stage3;}; 
		};
		debug_panic("list_prev_count is over\n"); 
		stage3:;
		return;
	};
	
	
	
#endif




