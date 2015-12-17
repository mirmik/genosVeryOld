#ifndef GENOS_DFFS
	#define GENOS_DFFS
	
	
	#include "genos/drv/dataflash/dataflash_drv.h"
	
	#define BLOCK_INODE_OFFSET 4
	#define INODES_ON_PAGE 8
	
	struct dffs_inode
	{
	char name[16];
	size_t blocks[12];	
	char stb[24];
	};
	
	
	struct dffs_inode_block
	{
		dffs_inode blocks[8];	
		char stb[16];
	};
	
	static dffs_inode dffs_get_inode(size_t n)
	{
		dffs_inode_block blk;
		dfdrv_read_block((uint8_t*)&blk, n/INODES_ON_PAGE + BLOCK_INODE_OFFSET);
		return blk.blocks[n%INODES_ON_PAGE];
	};
	
	//static void dffs_write_inode(dffs_inode inode, size_t n)
	//{
	//	dffs_inode_block blk;
	//	dfdrv_read_block((uint8_t*)&blk, n/INODES_ON_PAGE + BLOCK_INODE_OFFSET);
	//};
	
	
	
	
	
#endif