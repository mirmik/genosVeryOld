#ifndef GENOS_MFS_BLOCK
	#define GENOS_MFS_BLOCK
	
	#include "genos/memory/la_alloc.h"
	#include "genos/debug/debug.h"
	
	class mfs_file_page_header{
		public:
		list_head lst;
		size_t sz;
		char* outop(){return (char*)(this+1);};
	};
	
	
	class mfs_file
	{
		public:
		list_head head;
		size_t page_sz = 128;
		size_t pages = 0;
		size_t num;
		
		void expand(size_t n)
		{
			for(;n--;)
			{
				mfs_file_page_header* tmp = (mfs_file_page_header*)la_alloc(page_sz 
				+ sizeof(mfs_file_page_header));
				list_add_tail(&tmp->lst, &head);
				pages++;
				tmp->sz = page_sz;
				memset(tmp->outop(), 0, page_sz);
			};
		};
		
		void dump(){
			mfs_file_page_header* entry;
			list_for_each_entry(entry, &head, lst)
			{
				debug_print_dump(entry->outop(), page_sz);
			};
		};
		
	};
	
	void mfs_write(mfs_file* fl,const char* src, size_t pos, size_t len)
	{
		//Добавляем новые страницы, если нехватит.
		while ((pos + len) > (fl->pages * fl->page_sz)) fl->expand(1);
		
		//Листаем.
		size_t begin_page = pos / fl->page_sz;
		list_head* iter = fl->head.next;
		while(begin_page--) {iter = iter->next; pos -= fl->page_sz;};
		mfs_file_page_header* entry = list_entry(iter, mfs_file_page_header, lst);
		
		size_t _len;
		while(len != 0)
		{
			_len = (len > fl->page_sz - pos) ? fl->page_sz - pos : len;
			len -= _len;
			memcpy(entry->outop() + pos, src, _len);
			src = src + _len;
			pos = 0;
			iter = iter->next;
			entry = list_entry(iter, mfs_file_page_header, lst);
		};
		
		if (fl->num < pos + len) fl->num = pos + len;
	};
	
	int mfs_read(mfs_file* fl,char* dst, size_t pos, size_t len){
		
		if (fl->num - pos < 0) return 0;
		if (fl->num - pos - len < 0) len = fl->num - pos;
		
		size_t begin_page = pos / fl->page_sz;
		list_head* iter = fl->head.next;
		while(begin_page--) {iter = iter->next; pos -= fl->page_sz;};
		mfs_file_page_header* entry = list_entry(iter, mfs_file_page_header, lst);
		size_t llen = len;
		size_t _len;
		while(len != 0)
		{
			_len = (len > fl->page_sz - pos) ? fl->page_sz - pos : len;
			len -= _len;
			memcpy(dst, entry->outop() + pos,  _len);
			dst = dst + _len;
			pos = 0;
			iter = iter->next;
			entry = list_entry(iter, mfs_file_page_header, lst);
		};
		
		return llen;
	};
	
	
	
	
	
	
	
	
	
	
	
	
	
#endif