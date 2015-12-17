#ifndef GENOS_VFS
	#define GENOS_VFS
	
	
	#include "genos/types.h"
	#include "genos/base_struct/list.h"
	
	extern list_head super_list;
	
	
	#define FS_CHARDEVICE  0x03
	#define FS_BLOCKDEVICE 0x04
	#define FS_PIPE        0x05
	#define FS_SYMLINK     0x06
	#define FS_MOUNTPOINT  0x08 // Файл является активной точкой монтирования?
	
	
	struct fs_node;
	
	struct dirent // One of these is returned by the readdir call, according to POSIX.
	{
		char name[10]; // Имя файла..
		//size_t ino;     // Номер inode. Требеся для POSIX.
	}; 
	
	typedef size_t (*read_type)(fs_node*,size_t, size_t, uint8_t*);
	typedef size_t (*write_type)(fs_node*,size_t, size_t, uint8_t*);
	typedef void (*open_type)(fs_node*);
	typedef void (*close_type)(fs_node*);
	typedef dirent * (*readdir_type)(fs_node*, size_t);
	typedef fs_node * (*finddir_type)(fs_node*, char *name); 
	
	
	struct fs_operation
	{
		read_type read;
		write_type write;
		open_type open;
		close_type close;
		readdir_type readdir;
		finddir_type finddir;		
	}; 
	
	struct fs_node
	{
		char name[10];     // Имя файла.
		size_t flags;       // Включает тип нода.
		size_t length;      // Размер файла в байтах.
		fs_operation* fs_op;
		fs_node* ptr; // Используется для точек монтирования и символических ссылок.
	}; 
	
	
	
	extern fs_node *fs_root; // The root of the filesystem.
	
	// Стандартные функции чтения, записи, открытия, закрытия. Обратите внимание,
	//  что у них всех используется суффикс _fs с тем, чтобы отличать от функций чтения, 
	// записи, открытия и закрытия дескрипторов файлов, а не нодов файлов. 
	size_t read_fs(fs_node *node, size_t offset, size_t size, uint8_t *buffer);
	size_t write_fs(fs_node *node, size_t offset, size_t size, uint8_t *buffer);
	void open_fs(fs_node *node, uint8_t read, uint8_t write);
	void close_fs(fs_node *node);
	struct dirent *readdir_fs(fs_node *node, size_t index);
	fs_node *finddir_fs(fs_node *node, char *name); 
	
	
	
	
	
	
	
	
	
	
	
	
	
#endif