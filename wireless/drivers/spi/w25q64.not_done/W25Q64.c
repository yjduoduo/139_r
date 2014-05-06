#include "includeall.h"
#include "W25Q64.h"

//#define RDSR 		0x05 /*read status register-1*/
//#define RDSR2 		0x35 /*read status register-2*/
//#define VSRWE 		0x50 /*volatile SR write enable*/
//#define WRSR 		0x01 /*write status register*/
//#define WRDI 		0x04
//#define WRITENABLE 	0x06 /*write enable*/




//#define PAGE_PROG 0x02


//#define READ 0x03


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
static void SPI_CS_HIGH(void)
{
    FIO0SET |= 1<<16;
}
static void SPI_CS_LOW(void)
{
    FIO0CLR |= 1<<16;
}
void EnterNoInt(void)
{

}
void ExitNoInt(void)
{

}


void SPI0_init(void)
{
    PCONP 	|= (1 << 21);
    //wp
    PINSEL4 &= ~(0x3<<12);//clear P2.6
    PINSEL4 |= (0x0<<12);//P2.6,Func[0]
    FIO2DIR |= (0x1<<6);//dir P2.6,output
    FIO2CLR &= ~(0x1<<6);//level P2.6,low
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
    //cs
    PINSEL1 &= ~(0x3<<0);//clear P0.16
    PINSEL1 |= (0x0<<0);//P0.16,Func[0]
    FIO0DIR |= (0x1<<16);//dir P0.16,output
    FIO0SET |= (0x1<<16);//level P0.16,high

    //sck0
    PINSEL0 &= ~(0x1<<30);//clear P0.15
    PINSEL0 |= ((unsigned int)0x2<<30);//P0.15,Func[2]
    //miso0
    PINSEL1 &= ~(0x3<<2);//clear P0.17
    PINSEL1 |= (0x2<<2);//P0.17,Func[2]
    //mosi0
    PINSEL1 &= ~(0x3<<4);//clear P0.18
    PINSEL1 |= (0x2<<4);//P0.18,Func[2]

    //    SPI_WR_HIGH();
    SPI_WR_LOW();//WR拉低
    SPI_HOLD_HIGH();//HLOD拉高
    SPI_CS_HIGH();//CS拉高 不选中

    SSP0CR0 = (0x00 << 8)               				/* SCR  设置SPI时钟分频	        */
            | (0x00 << 7)                			/* CPHA 时钟输出相位	        */
            | (0x00 << 6)                     /* CPOL 时钟输出极性            */
            | (0x00 << 4)                     /* FRF  帧格式 00=SPI           */
            | (0x07 << 0);                    /* DSS  数据长度,0111=8位       */

    SSP0CR1 = (0x00 << 3)                       /* SOD  从机输出禁能,0=允许	    */
            | (0x00 << 2)                     /* MS   主从选择,0=主机,1=从机  */
            | (0x01 << 1)                     /* SSE  SSP使能                 */
            | (0x00 << 0);                    /* LBM  回写模式	            */
    SSP0CPSR = 0x52;			    		  /* 设置SSP从PCLK获得的分频值,   */
    SPI_CS_HIGH();//CS拉高                      /* 主模式下有效, 最小值为0x02   */

}


/*********************************************************************************************************
** Function name:		SSP_SendData
** Descriptions:		SSP接口向SSP总线发送数据
** input parameters:	data        待发送的数据
** output parameters:	返回值为读取的数据
*********************************************************************************************************/
uint8 SPISendByte(uint8 tmp)
{
    //    /* Put the data on the FIFO */
    while (!(SSP0SR & ((uint8)(1<<1))));//full,wait
    SSP0DR = tmp;
    /* Wait for sending to complete */
    while (SSP0SR & ((uint8)(1<<4)));//busy ,wait
    /* Return the received value */
    return (SSP0DR);
}

/*****************************************************************
** function name  :	 SPIReceiveByte
** description    :  SPI1 receive byte
******************************************************************/
uint8 SPIReceiveByte(void)
{
    /* Put the data on the FIFO */
    while ((SSP0SR & ((uint8)(1<<3))));//full,wait
    /* Put the data on the FIFO */
    SSP0DR = 0xff;
    /* Wait for sending to complete */
    while (SSP0SR & ((uint8)(1<<4)));//busy,wait

    /* Return the received value */
    return (SSP0DR);
}
#if 1
/******************************************************************************/
/* 函数名称：uint8 check_flash_busy(void)                                     */
/* 功能描述：检查flash是否忙                                                  */
/* 参数说明：无                                                               */
/* 参数返回: 如果忙返回1，不忙返回0                                           */
/******************************************************************************/ 
static uint8 Check_Flash_Busy(void)
{
    uint8 busy_flag = 0;
    SPI_CS_LOW();                     //置cs低选中
    SPISendByte(CMD1_READ_SR_1);
    busy_flag=SPIReceiveByte();
    SPI_CS_HIGH();                     //置cs高不选中

    return (busy_flag & 0x01);
}
#else
/*******************************************************************************
* Function Name  : u8 W25Q64_Busy(void)
* Description    : 状态检测
*                  最低位WIP为1则正在工作
* Input          : None
* Output         : None
* Return         : return (sta & 0x01);
*******************************************************************************/
static uint8 Check_Flash_Busy(void)
{
    uint8 tmp,tmp1;
    tmp1=5;
    SPI_CS_LOW();
    SPISendByte(RDSR);
    tmp = SPISendByte(0XFF);
    SPI_CS_HIGH();
    for(;tmp1>0;tmp1--);
    //    lcd_printf("busy:%d\n",(tmp & 0x01));
    return (tmp & 0x01);
}
#endif


//void SPI_Flash_ReadDeviceID(uint8 *databuffer)
//{
//    uint8 i;
//    lcd_printf("-->>get manufacturer/Device ID\n");
//    EnterNoInt();
//    SPI_CS_LOW();            //置cs低选中
//    SPISendByte(0x90);
//    SPISendByte(0xff);     //这里发送的三个字节是任意的，不一定是0xff
//    SPISendByte(0xff);
//    SPISendByte(0x00);
//    for(i=0;i<2;i++)
//    {
//        *databuffer=SPIReceiveByte();
//        databuffer++;
//    }
//    SPI_CS_HIGH();
//    ExitNoInt();
//}

//读取芯片ID
//返回值如下:
//0XEF13,表示芯片型号为W25Q80
//0XEF14,表示芯片型号为W25Q16
//0XEF15,表示芯片型号为W25Q32
//0XEF16,表示芯片型号为W25Q64
//0XEF18, W25Q64FVSFIF
uint16 SPI_Flash_Read_MANU_DEVICE_ID(void)
{
    uint16 Temp = 0;

    SPI_CS_LOW();
    SPISendByte(CMD1_MANU_DEVICE_ID);//发送读取ID命令
    SPISendByte(0x00);
    SPISendByte(0x00);
    SPISendByte(0x00);
    Temp|=SPIReceiveByte()<<8;
    Temp|=SPIReceiveByte();
    SPI_CS_HIGH();
    return Temp;
}
/********************************************
**函 数 名：SPI_Flash_ReadUniqueID
**功能描述：读取芯片唯一ID号，总共8字节
*********************************************/
uint8 SPI_Flash_ReadUniqueID(void)
{
    uint8 Temp = 0;
    SPI_CS_LOW();
    SPISendByte(CMD1_READ_UNIQUE_ID);//发送读取ID命令
    SPISendByte(0x00);
    SPISendByte(0x00);
    SPISendByte(0x00);
    SPISendByte(0x00);
    Temp=SPIReceiveByte();
    SPI_CS_HIGH();
    return Temp;

}

/********************************************
**函 数 名：SPI_Flash_Read_JEDECID
**功能描述：读取芯片JEDECID，总共24字节
*********************************************/
uint32 SPI_Flash_Read_JEDECID(void)
{
    uint32 Temp = 0;
    SPI_CS_LOW();
    SPISendByte(CMD1_JEDEC_ID);//发送读取ID命令
    Temp|=SPIReceiveByte()<<16;
    Temp|=SPIReceiveByte()<<8;
    Temp|=SPIReceiveByte();
    SPI_CS_HIGH();
    return Temp;

}

/********************************************
**函 数 名：SPI_Flash_Read_ReleasePowerDownID
**功能描述：读取芯片PowerDownID，总共8字节
*********************************************/
uint8 SPI_Flash_Read_ReleasePowerDownID(void)
{
    uint8 Temp = 0;
    SPI_CS_LOW();
    SPISendByte(CMD1_RELEASE_POWERDOWN_ID);//发送读取ID命令
    SPISendByte(0x00);
    SPISendByte(0x00);
    SPISendByte(0x00);
    Temp=SPIReceiveByte();
    SPI_CS_HIGH();
    return Temp;
}

/********************************************
**函 数 名：SPI_Flash_Read_Data
**功能描述：读取flash内容，总共8字节
*********************************************/
uint8 SPI_Flash_Read_Data(uint32 address)
{
    uint8 Temp = 0;
    uint8 addr[3]={0,};
    addr[0] = (address & 0x00ff0000) >> 16;//bit 16~23
    addr[1] = (address & 0x0000ff00) >> 8; //bit 8~15
    addr[2] = (address & 0x000000ff);      //bit 0~7

    SPI_CS_LOW();
    SPISendByte(CMD1_READ_DATA);
    SPISendByte(addr[0]);
    SPISendByte(addr[1]);
    SPISendByte(addr[2]);
    Temp=SPIReceiveByte();
    SPI_CS_HIGH();
    return Temp;
}
/********************************************
**函 数 名：SPI_Flash_Fast_Read
**功能描述：读取flash内容，总共8字节
*********************************************/
uint8 SPI_Flash_Fast_Read(uint32 address)
{
    uint8 Temp = 0;
    uint8 addr[3]={0,};
    addr[0] = (address & 0x00ff0000) >> 16;//bit 16~23
    addr[1] = (address & 0x0000ff00) >> 8; //bit 8~15
    addr[2] = (address & 0x000000ff);      //bit 0~7

    SPI_CS_LOW();
    SPISendByte(CMD1_FAST_READ);
    SPISendByte(addr[0]);
    SPISendByte(addr[1]);
    SPISendByte(addr[2]);
    SPISendByte(0x00);
    Temp=SPIReceiveByte();
    SPI_CS_HIGH();
    return Temp;
}

/********************************************
**函 数 名：SPI_Flash_Send_1Cmd
**功能描述：发送一条命令
*********************************************/
static void SPI_Flash_Send_1Cmd(uint8 cmd)
{
    SPI_CS_LOW();
    SPISendByte(cmd);
    SPI_CS_HIGH();
}
/********************************************
**函 数 名：SPI_Flash_Write_Enable
**功能描述：允许读
*********************************************/
static void SPI_Flash_Write_Enable(void)
{
    SPI_Flash_Send_1Cmd(CMD1_WRITEENABLE);
}
/********************************************
**函 数 名：SPI_Flash_Write_Disable
**功能描述：禁止读
*********************************************/
static void SPI_Flash_Write_Disable(void)
{
    SPI_Flash_Send_1Cmd(CMD1_WRITEDISABLE);
}
/********************************************
**函 数 名：SPI_Flash_Vo_SR_WriteEnable
**功能描述：volatile SR wirte enable
*********************************************/
static void SPI_Flash_Vo_SR_WriteEnable(void)
{
    SPI_Flash_Send_1Cmd(CMD1_VSR_WRITEENABLE);
}
/******************************************************************************/
/* 函数名称：SPI_Flash_Read_Status_Reg1                                     */
/* 功能描述：读取 SR1的各种状态                                                  */
/******************************************************************************/
uint8 SPI_Flash_Read_Status_Reg1(void)
{
    uint8 busy_flag = 0;
    SPI_CS_LOW();                     //置cs低选中
    SPISendByte(CMD1_READ_SR_1);
    busy_flag=SPIReceiveByte();
    SPI_CS_HIGH();                     //置cs高不选中

    return (busy_flag);
}
/******************************************************************************/
/* 函数名称：SPI_Flash_Read_Status_Reg2                                     */
/* 功能描述：读取 SR1的各种状态                                                  */
/******************************************************************************/
uint8 SPI_Flash_Read_Status_Reg2(void)
{
    uint8 busy_flag = 0;
    SPI_CS_LOW();                     //置cs低选中
    SPISendByte(CMD1_READ_SR_2);
    busy_flag=SPIReceiveByte();
    SPI_CS_HIGH();                     //置cs高不选中

    return (busy_flag);
}
/******************************************************************************/
/* 函数名称：SPI_Flash_Write_Status_Reg                                     */
/* 功能描述：写状态寄存器                                                  */
/******************************************************************************/
void SPI_Flash_Write_Status_Reg(uint16 cmd)
{
    SPI_CS_LOW();                     //置cs低选中
    SPISendByte(CMD1_WRITE_SR);
    SPISendByte((uint8)cmd);
    SPISendByte((uint8)cmd>>8);
    SPI_CS_HIGH();                     //置cs高不选中
}
/******************************************************************************/
/* 函数名称：SPI_Flash_Page_Program                                     */
/* 功能描述：写数据                                                  */
/******************************************************************************/
void SPI_Flash_Page_Program(uint32 address,
                            uint8* data,
                            uint16 len)
{
    uint8 addr[3]={0,};
    uint16 num=0;
    addr[0] = (address & 0x00ff0000) >> 16;//bit 16~23
    addr[1] = (address & 0x0000ff00) >> 8; //bit 8~15
    addr[2] = (address & 0x000000ff);      //bit 0~7

    if(len > 256)
    {
        lcd_printf("Warning!!page program maybe overwrite!!\n");
    }

    SPI_CS_LOW();
    SPISendByte(CMD1_PAGE_PROGRAM);
    SPISendByte(addr[0]);
    SPISendByte(addr[1]);
    SPISendByte(addr[2]);
    for(num=0;num<len;num++)
    {
        SPISendByte(*data++);
    }
    SPI_CS_HIGH();
}
/******************************************************************************/
/* 函数名称：SPI_Flash_Sector_Erase                                     */
/* 功能描述：擦除一个扇区4K                                                  */
/******************************************************************************/
void SPI_Flash_Sector_Erase(uint32 address)
{
    uint8 addr[3]={0,};
    addr[0] = (address & 0x00ff0000) >> 16;//bit 16~23
    addr[1] = (address & 0x0000ff00) >> 8; //bit 8~15
    addr[2] = (address & 0x000000ff);      //bit 0~7

    SPI_CS_LOW();
    SPISendByte(CMD1_SECTOR_ERASE_4K);
    SPISendByte(addr[0]);
    SPISendByte(addr[1]);
    SPISendByte(addr[2]);
    SPI_CS_HIGH();
}
/******************************************************************************/
/* 函数名称：SPI_Flash_Block_Erase32K                                     */
/* 功能描述：擦除一个块32K                                                  */
/******************************************************************************/
void SPI_Flash_Block_Erase32K(uint32 address)
{
    uint8 addr[3]={0,};
    addr[0] = (address & 0x00ff0000) >> 16;//bit 16~23
    addr[1] = (address & 0x0000ff00) >> 8; //bit 8~15
    addr[2] = (address & 0x000000ff);      //bit 0~7

    SPI_CS_LOW();
    SPISendByte(CMD1_BLOCK_ERASE_32K);
    SPISendByte(addr[0]);
    SPISendByte(addr[1]);
    SPISendByte(addr[2]);
    SPI_CS_HIGH();
}
/******************************************************************************/
/* 函数名称：SPI_Flash_Block_Erase64K                                     */
/* 功能描述：擦除一个块64K                                                  */
/******************************************************************************/
void SPI_Flash_Block_Erase64K(uint32 address)
{
    uint8 addr[3]={0,};
    addr[0] = (address & 0x00ff0000) >> 16;//bit 16~23
    addr[1] = (address & 0x0000ff00) >> 8; //bit 8~15
    addr[2] = (address & 0x000000ff);      //bit 0~7

    SPI_CS_LOW();
    SPISendByte(CMD1_BLOCK_ERASE_64K);
    SPISendByte(addr[0]);
    SPISendByte(addr[1]);
    SPISendByte(addr[2]);
    SPI_CS_HIGH();
}

/******************************************************************************/
/* 函数名称：SPI_Flash_Chip_Erase                                     */
/* 功能描述：擦除整个芯片                                                  */
/******************************************************************************/
void SPI_Flash_Chip_Erase(void)
{
    SPI_CS_LOW();
    SPISendByte(CMD1_CHIP_ERASE);
    SPI_CS_HIGH();
}



///*******************************************************************************
//* Function Name  : u8 W25Q64_CMD1B_READ1B(u8 cmd)
//* Description    : 发送一个字节指令并接受返回值
//*                  This function must be used only if the Start_Read_Sequence
//*                  function has been previously called.
//* Input          : None
//* Output         : None
//* Return         : Byte Read from the SPI Flash.
//RDSR Read Status Register
//*******************************************************************************/
//uint8 W25Q64_CMD1B_READ1B(uint8 cmd)
//{
//    uint8 tmp;
//    SPI_CS_LOW();
//    SPISendByte(cmd);
//    tmp = SPIReceiveByte();
//    SPI_CS_HIGH();
//    lcd_printf("cmd:0x%x,val:%d\n",cmd,tmp);

//    return tmp;
//}

///*******************************************************************************
//* Function Name  : void W25Q64_CMD1B_S1B(u16 cmd , u16 data)
//* Description    : 写一指令与一数据
//* Input          : None
//* Output         : None
//* Return         : Byte Read from the SPI Flash.
//*******************************************************************************/
//void W25Q64_CMD1B_S1B(uint16 cmd , uint16 data)
//{
//    SPI_CS_LOW();
//    SPISendByte(cmd);
//    SPISendByte((uint8)data);
//    SPISendByte((uint8)(data>>8));
//    SPI_CS_HIGH();
//}
///*******************************************************************************
//* Function Name  : void W25Q64_CMD1B_S1B(u16 cmd , u16 data)
//* Description    : 写一指令与两数据
//* Input          : None
//* Output         : None
//* Return         : Byte Read from the SPI Flash.
//*******************************************************************************/
//void W25Q64_CMD1B_S2B(uint16 cmd , uint16 data,uint16 data2)
//{
//    SPI_CS_LOW();
//    SPISendByte(cmd);
//    SPISendByte((uint8)data);
//    SPISendByte((uint8)(data2));
//    SPI_CS_HIGH();
//}

///*************************************]\******************************************
//* Function Name  : void W25Q64_CMD1B(u8 cmd)
//* Description    : 发送一个字节指令
//*                  This function must be used only if the Start_Read_Sequence
//*                  function has been previously called.
//* Input          : None
//* Output         : None
//* Return         : Byte Read from the SPI Flash.
//*******************************************************************************/
//void W25Q64_CMD1B(uint8 cmd)
//{
//    SPI_CS_LOW();
//    SPISendByte(cmd);
//    SPI_CS_HIGH();
//}

///*******************************************************************************
//* Function Name  : void W25Q64_WP_En(void)
//* Description    : 写使能
//*                  使能寄存器中的WEL位
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void W25Q64_Write_En(void)
//{
//    uint16 tmp;
//    //清除 Block Protect位：PB0，PB1，PB2，即取消所有区域保护
//    //1000 0011  reserve:0111 1100 7c res:~7c
//    tmp = W25Q64_CMD1B_READ1B(RDSR) & (~0x7c);  /*& (~0x7c);*/ // ~00011100  1110 0011
//    //    lcd_printf("W25Q64_CMD1B_READ1B:%d\n",tmp);
//    W25Q64_CMD1B(VSRWE);/*volatile SR wirte enable should before WRSR*/
//    W25Q64_CMD1B_S1B(WRSR, tmp);
//    // Protected Area Upper sixteenth (Sector 15)以及WEL位
//    W25Q64_CMD1B(WRITENABLE);//write enable
//    SPI_WR_HIGH();  //write Protection diable .  added by xie
//}
///*******************************************************************************
//* Function Name  : void W25Q64_Write_CHIPEARSE_En(void)
//* Description    : 写使能
//*                  使能寄存器中的WEL位
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void W25Q64_Write_CHIPEARSE_En(void)
//{
//    uint8 tmp,tmp2;

//    W25Q64_CMD1B(WRITENABLE);
//    //清除 SEC,TB位，清除 Block Protect位：PB0，PB1，PB2，即取消所有区域保护
//    //1000 0011  reserve:0111 1100 7c res:~7c
//    tmp = W25Q64_CMD1B_READ1B(RDSR) & (0x83);  /*& (~0x7c);*/ // ~00011100  1110 0011
//    //1011 1111  reverse:0100 0000 40 rev:~40
//    tmp2= W25Q64_CMD1B_READ1B(RDSR2) & (0xbf);
//    //    lcd_printf("W25Q64_CMD1B_READ1B:%d\n",tmp);
////    W25Q64_CMD1B(VSRWE);/*volatile SR wirte enable should before WRSR*/

//    lcd_printf("tmp :%d\n",tmp);
//    lcd_printf("tmp2:%d\n",tmp2);
//    lcd_printf("tmp|tmp2<<8:%d\n",tmp|(tmp2<<8));
//    W25Q64_CMD1B_S2B(WRSR, tmp,tmp2);
//    // Protected Area Upper sixteenth (Sector 15)以及WEL位


////    lcd_printf("==>>read conf result!\n");
////    W25Q64_CMD1B_READ1B(RDSR);
//    SPI_WR_HIGH();  //write Protection diable .  added by xie
//}


///*******************************************************************************
//* Function Name  : void Flash_WP_En(void)
//* Description    : 写禁止
//*                  使能寄存器中的WEL位
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void W25Q64_WP_En(void)
//{
//    uint16 tmp;
//    //添加PB0，PB1，PB2的保护位
//    tmp = W25Q64_CMD1B_READ1B(RDSR) | 0x1c;
//    W25Q64_CMD1B(VSRWE);/*volatile SR wirte enable should before WRSR*/
//    W25Q64_CMD1B_S1B(WRSR, tmp);

//    W25Q64_CMD1B(WRDI);
//    SPI_WR_LOW();          //write Protection enable .  added by xie
//}
///*******************************************************************************
//* Function Name  : void Flash_WP_En(void)
//* Description    : 写禁止
//*                  使能寄存器中的WEL位
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void W25Q64_WP_CHIPEARSE_En(void)
//{
//    uint8 tmp,tmp2;
//    //添加PB0，PB1，PB2的保护位
//    tmp = W25Q64_CMD1B_READ1B(RDSR) | 0x1c;
//    tmp2 = W25Q64_CMD1B_READ1B(RDSR2) | 0x40;

//    W25Q64_CMD1B(VSRWE);/*volatile SR wirte enable should before WRSR*/
//    W25Q64_CMD1B_S1B(WRSR, tmp&(tmp2<<8));

//    W25Q64_CMD1B(WRDI);
//    SPI_WR_LOW();          //write Protection enable .  added by xie
//}


///********************************************************
//** 函 数 名：SectorErase 4k
//** 功能描述：扇区擦除
//** 参    数：扇区地址
//** 返    回：无
//*********************************************************/
//void Sector_4K_Erase(uint32 address)
//{
//    uint8 ad[3]/* , data*/;

//    ad[0] = (address & 0x00ff0000) >> 16;
//    ad[1] = (address & 0x0000ff00) >> 8;
//    ad[2] = (address & 0x000000ff);

//    // EnterNoInt();
//    W25Q64_Write_En();
//    SPI_CS_LOW();                      //置cs低选中
//    SPISendByte(0x20);
//    SPISendByte(ad[0]);
//    SPISendByte(ad[1]);
//    SPISendByte(ad[2]);
//    SPI_CS_HIGH();                      //置cs高不选中
//    while(Check_Flash_Busy());       //等待器件写完结束
//    W25Q64_WP_En();
//    // ExitNoInt();
//}
///********************************************************
//** 函 数 名：SectorErase 32k
//** 功能描述：扇区擦除
//** 参    数：扇区地址
//** 返    回：无
//*********************************************************/
//void Sector_32K_Erase(uint32 address)
//{
//    // EnterNoInt();
//    W25Q64_Write_En();					//写使能
//    SPI_CS_LOW();                      //置cs低选中
//    SPISendByte(0x52);
//    SPISendByte((uint8)(address>>16));
//    SPISendByte((uint8)(address>>8));
//    SPISendByte((uint8)address);
//    SPI_CS_HIGH();                      //置cs高不选中
//    while(Check_Flash_Busy());       //等待器件写完结束
//    W25Q64_WP_En();
//    // ExitNoInt();
//}
///********************************************************
//** 函 数 名：SectorErase 64k
//** 功能描述：扇区擦除
//** 参    数：扇区地址
//** 返    回：无
//*********************************************************/
//void Sector_64K_Erase(uint32 address)
//{
//#if 1
//    uint8 ad[3]/* , data*/;

//    ad[0] = (address & 0x00ff0000) >> 16;
//    ad[1] = (address & 0x0000ff00) >> 8;
//    ad[2] = (address & 0x000000ff);

//    // EnterNoInt();
//    //    W25Q64_Write_En();
//    W25Q64_Write_CHIPEARSE_En();
//    SPI_CS_LOW();                      //置cs低选中
//    SPISendByte(0xD8);//64k erase
//    SPISendByte(ad[0]);
//    SPISendByte(ad[1]);
//    SPISendByte(ad[2]);
//    SPI_CS_HIGH();                      //置cs高不选中
//    while(Check_Flash_Busy());       //等待器件写完结束
//    //    W25Q64_WP_En();
//    W25Q64_WP_CHIPEARSE_En();
//    // ExitNoInt();
//#else
//    // EnterNoInt();
//    W25Q64_Write_En();					//写使能
//    SPI_CS_LOW();                      //置cs低选中
//    SPISendByte(0xD8);
//    SPISendByte((uint8)(address>>16));
//    SPISendByte((uint8)(address>>8));
//    SPISendByte((uint8)address);
//    SPI_CS_HIGH();                      //置cs高不选中
//    while(Check_Flash_Busy());       //等待器件写完结束
//    W25Q64_WP_En();
//    // ExitNoInt();

//#endif
//}

///******************************************************************************
//** 函 数 名：FlashProgram
//** 功能描述: 向指定的地址写入指定数量的字节
//** 参    数：数据缓冲区，字节数，起始地址
//** 返    回：无
//******************************************************************************/
//void FlashProgram(uint8 *databuffer,uint16 datasize,uint32 address)
//{
//    uint8 ad[3]/* , data*/;


//    ad[0] = (address & 0x00ff0000) >> 16;
//    ad[1] = (address & 0x0000ff00) >> 8;
//    ad[2] = (address & 0x000000ff);

//    //  EnterNoInt();
//    W25Q64_Write_En();					//写使能
//    SPI_CS_LOW();                      //置cs低选中
//    SPISendByte(0x02);
//    SPISendByte(ad[0]);
//    SPISendByte(ad[1]);
//    SPISendByte(ad[2]);
//    while(datasize>0)
//    {
//        SPISendByte(*databuffer++);
//        datasize--;
//    }
//    SPI_CS_HIGH();                      //置cs高不选中


//    while(Check_Flash_Busy());       //等待器件写完结束
//    W25Q64_WP_En();

//    //   ExitNoInt();
//}
///*******************************************************************************
//* Function Name  : void M25P80_Write_1Byte(u32 addr , u8 data)
//* Description    : 写数据
//*                  写固定地址的一位数据
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void M25P80_Write_1Byte(uint32 addr , uint8 data)
//{
//    uint8 ad[3] ;
//    ad[0] = (addr & 0x00ff0000) >> 16;
//    ad[1] = (addr & 0x0000ff00) >> 8;
//    ad[2] = (addr & 0x000000ff);


//    W25Q64_Write_En();

//    SPI_CS_LOW();
//    SPISendByte(PAGE_PROG);
//    SPISendByte(ad[0]);
//    SPISendByte(ad[1]);
//    SPISendByte(ad[2]);
//    SPISendByte(data);//根据指令集，发送两次
//    SPISendByte(data);
//    SPI_CS_HIGH();


//    while(Check_Flash_Busy());
//    W25Q64_WP_En();
//}
///*******************************************************************************
//* Function Name  : void ChipErase(void)
//* Description    : 写数据
//*                  写固定地址的一位数据
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void ChipErase(void)
//{
//    //    while(Check_Flash_Busy());

//    W25Q64_Write_CHIPEARSE_En();
//    SPI_CS_LOW();
//    SPISendByte(0x60);
//    SPI_CS_HIGH();

//    while(Check_Flash_Busy());
//    W25Q64_WP_CHIPEARSE_En();

//}

///*****************************************************************
//** 函 数 名：ReadRFlash
//** 功能描述：从指定的地址读取指定数量的字节
//** 参    数：数据缓冲区，字节数，起始地址
//** 返    回：无
//******************************************************************/
//void ReadFlash(uint8 *databuffer,uint16 datasize,uint32 address)
//{
//    uint16 i;
//    // EnterNoInt();
//    SPI_CS_LOW();
//    SPISendByte(0x03);
//    SPISendByte((uint8)(address>>16));
//    SPISendByte((uint8)(address>>8));
//    SPISendByte((uint8)address);
//    for(i=0;i<datasize;i++)
//    {
//        databuffer[i]=SPIReceiveByte();
//    }
//    SPI_CS_HIGH();                 //置cs高不选中
//    //ExitNoInt();
//}
///*******************************************************************************
//* Function Name  : u8 W25Q64_Read_1Byte(u32 addr )
//* Description    : 读数据
//*                  读固定地址的一位数据
//* Input          : None
//* Output         : None
//* Return         : return data;
//*******************************************************************************/
//uint8 ReadFlash_1Byte(uint32 addr)
//{
//#if 0
//    uint8 ad[3] , data;

//    ad[0] = (addr & 0x00ff0000) >> 16;
//    ad[1] = (addr & 0x0000ff00) >> 8;
//    ad[2] = (addr & 0x000000ff);

//    SPI_CS_LOW();//选中
//    SPISendByte(READ);
//    SPISendByte(ad[0]);
//    SPISendByte(ad[1]);
//    SPISendByte(ad[2]);
//    data = SPISendByte(0xff);
//    SPI_CS_HIGH();//高阻
//    return data;
//#else
//    uint8 ad[3] , data;



//    ad[0] = (addr & 0x00ff0000) >> 16;
//    ad[1] = (addr & 0x0000ff00) >> 8;
//    ad[2] = (addr & 0x000000ff);

//    SPI_CS_LOW();//选中
//    SPISendByte(READ);
//    SPISendByte(ad[0]);
//    SPISendByte(ad[1]);
//    SPISendByte(ad[2]);
//    data = SPISendByte(0xff);
//    SPI_CS_HIGH();//高阻
//    //    lcd_printf("reveive data:%d\n",data);
//    return data;
//#endif
//}

///**************************************************************************
//** 函数名：CheckData
//** 功能描述：检验指定的Flash起始地址的数据和指定的缓冲区的数据是否全部相等
//** 参数：数据缓冲区DataBuffer, Flash起始地址DataAddr，数据字节数
//** 返回：全部相同返回1，否则返回0
//***************************************************************************/
//uint8 CheckData(uint8 *DataBuffer, uint32 DataAddr, uint16 DataSize)
//{
//    uint8 data;
//    uint16 i;
//    for(i=0;i<DataSize;i++)
//    {
//        ReadFlash(&data,1,DataAddr+i);
//        if(data!=DataBuffer[i])return 0;
//    }
//    return 1;
//}



/////////////////////////////////////////////////////


////static uint8_t  Check_Flash_Busy_W25Q(void)
////{

////    uint8_t busy_flag;

////    //    DrvSYS_Delay(2);
////    Delay1Ms(100);

////    SPI_CS_LOW();

////    SPISendByte(0x05);

////    busy_flag=SPIReceiveByte();

////    SPI_CS_HIGH();

////    lcd_printf("busy_flag=0x%x\n",busy_flag);

////    if(busy_flag & 0x01)
////    {
////        //if WEL or BUSY=1 ,busy_flag=1
////        busy_flag = 1;
////    }
////    else
////    {
////        //if WEL and BUSY=0 ,busy_flag=0
////        busy_flag = 0;
////    }

////    return busy_flag;

////}




////void ReadManufactDeviceID_90h_W25Q(void)
////{//

////    uint32_t val ;

////    uint32_t i ;

////    Check_Flash_Busy_W25Q();

////    SPI_CS_LOW();

////    SPISendByte(0x90);

////    SPISendByte(0x00);

////    SPISendByte(0x00);

////    SPISendByte(0x00);



////    lcd_printf("90h\n");

////    for(i=0;i<2;i++)
////    {
////        val=SPIReceiveByte();

////        lcd_printf("val=0x%x---%d\n",val,i);

////    }

////    SPI_CS_HIGH();
////}


