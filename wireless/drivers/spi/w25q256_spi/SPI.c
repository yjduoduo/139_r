/*****************************************START SPI***********************************************/
#include "SPI.h"


static void SPI_WR_HIGH(void)
{
    FIO2SET |= 1<<6;
}
static void SPI_WR_LOW(void)
{
    FIO2CLR |= 1<<6;
}
static void SPI_HOLD_HIGH(void)
{
    FIO2SET |= 1<<8;
}
static void SPI_HOLD_LOW(void)
{
    FIO2CLR |= 1<<8;
}
void SPI_CS_HIGH(void)
{
    //    Delay1Ms(10000);
    FIO0MASK = 0x00000000;
    FIO0SET |= (0x1<<16);
}
void SPI_CS_LOW(void)
{
    //    uint16 i;
    //    for(i=0;i<2000;i++)
    FIO0MASK = 0x00000000;
    FIO0CLR |= (0x1<<16);
    //    Delay1Ms(10000);
}
//FIOPIN?32??
uint32 pin016_status(void)
{
    lcd_printf("0x1<<16 is:0x%x\n",0x1<<16);
    return (FIO0PIN & (uint32)0x1<<16);
}

void EnterNoInt(void)
{

}
void ExitNoInt(void)
{

}

/*********************************************************************************************************
** Function name: 		SPIInit																									
** Descriptions:		初始化SPI为主机，并初始化相关引脚					
** input parameters: 	无																
** output parameters:	无																
*********************************************************************************************************/
void  SPIInit(void)
{  
    PCONP |=(0x1<<8);

    //wp
    PINSEL4 &= ~(0x3<<12);//clear P2.6
    PINSEL4 |= (0x0<<12);//P2.6,Func[0]
    FIO2DIR |= (0x1<<6);//dir P2.6,output
    FIO2SET |= (0x1<<6);//level P2.6,high
    //spi rst
    PINSEL4 &= ~(0x3<<14);//clear P2.7
    PINSEL4 |= (0x0<<14);//P2.7,Func[0]
    FIO2DIR |= (0x1<<7);//dir P2.7,output
    FIO2SET |= (0x1<<7);//level P2.7,high
    //hold
    PINSEL4 &= ~(0x3<<16);//clear P2.8
    PINSEL4 |= (0x0<<16);//P2.8,Func[0]
    FIO2DIR |= (0x1<<8);//dir P2.8,output
    FIO2SET |= (0x1<<8);//level P2.8,high
    //GPIO
    /*
    * 初始化P0.16为GPIO输出,用作片选脚
    */

    PINSEL1 &= ~(0x3<<0);//clear P0.16
    PINSEL1 |= (0x0<<0);//P0.16,Func[0]
    FIO0DIR |= (0x1<<16);//dir P0.16,output
    FIO0SET |= (0x1<<16);//level P0.16,high
    //sck
    PINSEL0 &= ~(0x1<<30);//clear P0.15
    PINSEL0 |= (unsigned int)(0x3<<30);//P0.15,Func[2]
    //miso
    PINSEL1 &= ~(0x3<<2);//clear P0.17
    PINSEL1 |= (0x3<<2);//P0.17,Func[2]
    //mosi
    PINSEL1 &= ~(0x3<<4);//clear P0.18
    PINSEL1 |= (0x3<<4);//P0.18,Func[2]

    //    SPI_WR_LOW();//WR??
    SPI_WR_HIGH();
    SPI_HOLD_HIGH();//HLOD??
    SPI_CS_HIGH();//CS?? ??
    //
    /*
    * 设置SPI的工作方式
    */
    S0SPCR   = 	(0 << 3) 					                            /* CPHA = 0, 数据在SCK 的       */                                                           /* 第一个时钟沿采样	            */
            |	(0 << 4) 					                            /* CPOL = 0, SCK 为高电平有效   */
            |	(1 << 5) 					                            /* MSTR = 1, SPI 处于主模式     */
            |	(0 << 6) 					                            /* LSBF = 0, SPI数据传输MSB     */
            |	(0 << 7);					                            /* SPIE = 0, SPI 中断被禁止     */

    S0SPCCR  = 0x52;						                            /* 设置SPI时钟分频              */
}

void  SPI_SendData(INT8U data)
{  
    S0SPDR  = data;
    while (0 == (S0SPSR & 0x80));			// 等待SPIF置位，即等待数据发送完毕
    S0SPSR  = 0;							// 清除SPIF标志
}
void SPI_SetData(INT8U data)
{
    FIO0CLR |= SLAVE_CS;
    S0SPDR  = data;
    while (0 == (S0SPSR & 0x80));			// 等待SPIF置位，即等待数据发送完毕
    S0SPSR  = 0;
    FIO0SET |= SLAVE_CS;
}
INT8U SPI_ReadByte(void)
{
    INT8U data;
    S0SPDR = 0xFF;							//没有任何意义，只为了产生时钟，将数据读回来。
    while (0 == (S0SPSR & 0x80));			// 等待SPIF置位，即等待数据发送完毕
    S0SPSR  = 0;							// 清除SPIF标志
    data = S0SPDR;
    return data;
}
void SPI_BulK_Ease(void)
{
    SPI_SendData(WREN);
    SPI_SendData(BE);
}
void SPI_Sector_Ease(INT8U *address)
{
    SPI_SendData(WREN);
    FIO0CLR |= SLAVE_CS;
    SPI_SetData(SE);
    SPI_SetData(*address);
    SPI_SetData(*(address + 1));
    SPI_SetData(*(address + 2));
    FIO0SET |= SLAVE_CS;
}
INT8U Read_Status(void)
{
    INT8U data;
    FIO0CLR |= SLAVE_CS;
    SPI_SetData(RDSR);
    data = SPI_ReadByte();
    FIO0SET |= SLAVE_CS;
    return data;
}
INT8U SPI_Write_Status(INT8U status)
{
    if( 1 == (Read_Status() & 0x01) )
    {
        return FALSE;
    }
    else
    {
        SPI_SendData(WREN);
        FIO0CLR |= SLAVE_CS;
        SPI_SetData(WRSR);
        SPI_SetData(status);
        FIO0SET |= SLAVE_CS;
        return TRUE;
    }
}
INT8U SPI_Read_Data(INT8U *address,INT8U *rdata,INT32U length)
{
    INT32U i;
    while(Read_Status() & 0x01);
    FIO0CLR |= SLAVE_CS;
    SPI_SetData(READ);
    SPI_SetData(*address);
    SPI_SetData(*(address + 1));
    SPI_SetData(*(address + 2));
    for(i = 0;i < length;i++)
    {
        *(rdata + i) = SPI_ReadByte();
    }
    FIO0SET |= SLAVE_CS;
    return TRUE;
}
INT8U SPI_Write_Data(INT8U *address,INT8U *sdata,INT32U length)
{
    INT32U i;
    while(Read_Status() & 0x01);
    SPI_SendData(WREN);
    FIO0CLR |= SLAVE_CS;
    SPI_SetData(PP);
    SPI_SetData(*address);
    SPI_SetData(*(address + 1));
    SPI_SetData(*(address + 2));
    for(i = 0;i < length;i++)
    {
        SPI_SetData(*(sdata + i));
    }
    FIO0SET |= SLAVE_CS;
    return TRUE;
}
volatile INT8U data[3];
void read_jedecID(void)
{

    INT8U num=0;
    FIO0CLR |= SLAVE_CS;

    SPI_SendData(0x9F);
    data[num] = SPI_ReadByte();num++;
    data[num] = SPI_ReadByte();num++;
    data[num] = SPI_ReadByte();num++;


    FIO0SET |= SLAVE_CS;

    lcd_printf("jedec id:0x%x,0x%x,0x%x\n",data[0],data[1],data[2]);
}
void read_jedecID2(void)
{
    INT8U num=0;
    FIO0CLR |= SLAVE_CS;

    SPI_SendData(0x9F);
    data[num] = SPI_ReadByte();num++;
    data[num] = SPI_ReadByte();num++;
    data[num] = SPI_ReadByte();num++;


    FIO0SET |= SLAVE_CS;

    lcd_printf("222:jedec id:0x%x,0x%x,0x%x\n",data[0],data[1],data[2]);


}

/*****************************************End file************************************************/


