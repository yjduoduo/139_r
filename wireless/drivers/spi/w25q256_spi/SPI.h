/**************************************************start file**********************************************************/
#ifndef	_SPI_H
#define _SPI_H
#include "includeall.h"

#define     SLAVE_CS        (1 << 16)                                   /*  从机片选口	                */

#define		WREN	0x06
#define		WRDI	0x04
#define		RDSR	0x05
#define		WRSR	0x01
#define		READ	0x03
#define		FAST_READ	0x0B
#define		PP		0x02
#define		SE		0xD8
#define 	BE 		0xC7
#define		DP		0xB9
#define		RES		0xAB
void  SPIInit(void);
void  SPI_SendData(INT8U data);
void  SPI_SetData(INT8U data);
INT8U SPI_ReadByte(void);
void  SPI_BulK_Ease(void);
void  SPI_Sector_Ease(INT8U *addres);
INT8U Read_Status(void);
INT8U SPI_Write_Status(INT8U status);
INT8U SPI_Read_Data(INT8U *address,INT8U *rdata,INT32U length);
INT8U SPI_Write_Data(INT8U *address,INT8U *sdata,INT32U length);



void read_jedecID(void);
#endif

/**************************************************end file************************************************************/

