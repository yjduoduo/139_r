#ifndef M25P80_H
#define M25P80_H
#include "includeall.h"



#ifdef EXTERN_M25P80
#define EXT_M25P80
#else
#define EXT_M25P80 extern
#endif



/* ATMEL SEEPROM command set */
// #define WRITE		0x02
#define WREN  0X06    //дʹ��  MSB A8 is set to 0, simplifying test
#define WRDI  0X04    //д��ֹ
#define RDSR  0X05    //��״̬�Ĵ���
#define WRSR  0X01    //д״̬�Ĵ�����WELΪ0������д
#define READ  0X03    //���ֽ�
#define FAST_READ 0X0B    //���ָ��
#define PP  0X02           //ҳдָ��
#define SE  0XD8           //�������
#define BE  0XC7           //������
#define DP  0XB9           //��ȵ���ģʽ
#define RES  0XAB           //����ȵ���ģʽ����

#define	SPI_CS			0x01							/* P0.6       */
#define	SPI_WR			0x01							/* P0.4        */
#define	SPI_HOLD		0x01							/* P0.5       */


#define	SPI_SEND_MODE	0x01
#define	SPI_RCB_MODE	0x10
#define	SPI_IDEL_BYTE	0x00


EXT_M25P80 void MP25P80_WriteEnable(void);
EXT_M25P80 void MP25P80_WriteDis(void);
EXT_M25P80 void MP25P80_EraseSector(long Addr);
EXT_M25P80 void MP25P80_EraseBulk(void);
EXT_M25P80 uchar MP25P80_ReadReg(void);
EXT_M25P80 void MP25P80_Check(void);







#endif // M25P80_H
