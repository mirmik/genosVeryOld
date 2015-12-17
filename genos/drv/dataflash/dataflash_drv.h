#ifndef DATAFLASH_DRV
	#define DATAFLASH_DRV
	
	
	#include "genos/drv/dataflash/dataflash.h"
	#include "genos/debug/debug.h"
	
	#define DFDRV_BLOCK_SIZE 528
	
	using dfdrv_block = uint8_t[DFDRV_BLOCK_SIZE];
	
	static void dfdrv_init() 
	{
		df_Init();
	}; 
	
	static void dfdrv_read_block(uint8_t* Buffer, size_t page)
	{
		df_PageFunc(DF_FLASH_TO_BUF2, page);
		df_GetStr( 2, 0, DFDRV_BLOCK_SIZE, Buffer);
	}; 
	
	
	static void dfdrv_write_block(uint8_t* Buffer, size_t page)
	{
		df_WriteStr( 2, 0, DFDRV_BLOCK_SIZE, Buffer);
		df_PageFunc(DF_BUF2_TO_FLASH_WITH_ERASE, page);
	}; 
	
	static void dfdrv_block_dump(size_t page)
	{
		uint8_t Buffer[DFDRV_BLOCK_SIZE];
		df_PageFunc(DF_FLASH_TO_BUF2, page);
		df_GetStr( 2, 0, DFDRV_BLOCK_SIZE, Buffer);
		debug_print_dump(Buffer, DFDRV_BLOCK_SIZE);
	}; 
	
	static void dfdrv_block_dump_ascii(size_t page)
	{
		uint8_t Buffer[DFDRV_BLOCK_SIZE];
		df_PageFunc(DF_FLASH_TO_BUF2, page);
		df_GetStr( 2, 0, DFDRV_BLOCK_SIZE, Buffer);
		debug_print_dump_ascii(Buffer, DFDRV_BLOCK_SIZE);
	}; 
	
	
	/*static void dfdrv_write_part_block (
	const BYTE* buff,	*/	/* Pointer to the data to be written, NULL:Initiate/Finalize write operation */
	/*DWORD sc	*/	/* Sector number (LBA) or Number of bytes to send */
	//)
	//{
		
	//}; 
	
	static void dfdrv_read_part_block(
	uint8_t* buff,		/* Pointer to the destination object */
	size_t sector,	/* Sector number (LBA) */
	uint8_t offset,	/* Offset in the sector */
	uint8_t count		/* Byte count (bit15:destination) */
	)
	{
		df_PageFunc(DF_FLASH_TO_BUF2, sector);
		df_GetStr( 2, offset, count, buff);
	}; 
	
	
#endif