/*************************************************************************************
*
*  ������� Atmel DataFlash
*
*  by:      BSVi
*  version: 1.00
*
*************************************************************************************/

#include "genos/types.h"
#include "avr/io.h"
#include "avr/delay.h"

#define DF_MISO_PB   8
#define DF_MOSI_PB   4
#define DF_SCK_PB    2
#define DF_SS_PB     1
#define DF_RESET_PB  1

#ifndef _DATA_FLASH_H
#define _DATA_FLASH_H

// � ���� ����� ���� ������� �������� �������. ��������� ����������
// � ����������� � ������������ ���������� ���������� ������� ����� �
// "�����" ���� ������� � ����� dataflash.cpp
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint8_t uint8;


// ��������������� ��� �������, ����� ��������� ��������������� ���� ������������
// ���������� dataflash �� ����� ���������� ���������

// ��������������� ��� �������, ���� ����� df_LinearSpace �� ������������
#define DF_ENABLE_LINEAR_SPACE

// �������� ������������ ������������ ����������.
struct df_Info_t
{
   uint16  pages;       // ���������� �������
   uint16  page_size;   // ������ �������� � ������
   uint8   page_bit;    // ����� ������ ��������
   uint8   chip_id;     // ��� ����������
};

extern df_Info_t df_Info;
uint8 df_GetStatus();
// ���������� S_OK ���� ���������� ����������. ����� ������ ���� �������,
// ��������� ����������� ���������� ����� ������ �� ��������� df_Info
void df_Init();

// �������� ����������� �� ���������� ��������. ������ ������� ��� ���������
// ���������� ��������. ��� ������������� ������������ ��� �������.
bool df_isReady();

// ������ � ������ � ������. ��. dataflash.cpp
void df_WriteStr( uint8 BufferNo, uint16 Addr, uint16 Count, uint8 *BufferPtr );
void df_WriteByte( uint8 BufferNo, uint16 Addr, uint8 Data );

void df_GetStr( uint8 BufferNo, uint16 Addr, uint16 Count, uint8 *BufferPtr );
uint8 df_GetChar(uint8 BufferNo, uint16 Addr );

// ������ ��������������� �� ����-������
void df_FlashRead( uint16 PageAdr, uint16 Addr, uint16 Count, uint8 *BufferPtr );

void df_PageFunc( uint16 PageCmd, uint16 PageAdr );
/*****************************************************************************
*  ���� ������� ��� ������������� � df_PageFunc
******************************************************************************/
#define DF_FLASH_TO_BUF1 		0x53	/* Main memory page to buffer 1 transfer  */
#define DF_FLASH_TO_BUF2 		0x55	/* Main memory page to buffer 2 transfer */
#define DF_BUF1_TO_FLASH_WITH_ERASE   	0x83	/* Buffer 1 to main memory page program with built-in erase */
#define DF_BUF2_TO_FLASH_WITH_ERASE   	0x86	/* Buffer 2 to main memory page program with built-in erase */
#define DF_BUF1_TO_FLASH_WITHOUT_ERASE  0x88	/* Buffer 1 to main memory page program without built-in erase */
#define DF_BUF2_TO_FLASH_WITHOUT_ERASE  0x89	/* Buffer 2 to main memory page program without built-in erase */


/*****************************************************************************
*  ���������� ��� �������� ������ � ������ ����������
******************************************************************************/
#ifdef DF_ENABLE_LINEAR_SPACE
// ����� ������������ dataflash ��� �������� ������������ � ��������� ������������ ��
// ������������� ������� �� ���������� ������, �������������� �������, �� �����������,
// ��������� � ��������� �/�� ��������. �� ������ ������� ������� �� ����� ��������
// �������� �������.
//
// ���� ������������� ��� ������ ������ - Write � UnsafeWrite. Write ������ ���������� ������
// � ������������ ������ �� � ��� �����������. UnsafeWrite �������������  ��� ����������������
// ������ ��������� ������ ������. ����� ���������� ���������������� ������� UnsafeWrite ����� �����
// ������ ��������� � dataflash ������ ���� ������ ����� Finalize, ����� ���������� �������
// ����� ���� ���������� �� ����, ��� ����� ���������� � �������� ����-������.
//
// GoToZero ���������� �� GoTo(0) ���, ��� ������ �������� ����������� �������.
//
// ��� ������� �� ���������� �������� �� ����������� ������ ������. �� ������ ���� ������� �� ����.
// ������ ���������� ���� �� ������� ����� �� ����� ������ ����� ������� SpaceToEnd
//
// ����� ��������� �������� ����������� ���������� ��. dataflash.cpp

class df_LinearSpace
{
  private:
   uint16 page;
   uint16 address;
   static uint16 page_in_buffer1;

  public:
   inline df_LinearSpace() { GoToZero(); }
   void GoToZero();
   uint32 SpaceToEnd();
   void Finalize();
   void Read( uint8 *buffer, uint16 count );
   void UnsafeWrite( uint8 *buffer, uint16 count );
   void Write( uint8 *buffer, uint16 count ) { UnsafeWrite(buffer, count); Finalize();}
   void SeekForward(  uint32 displacement );
   void SeekBackward(  uint32 displacement );
   void GoTo( uint32 location );
};

#endif /* DF_ENABLE_LINEAR_SPACE */




#endif /* _DATA_FLASH_H */
