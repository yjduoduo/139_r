#ifndef _W25Q64_H
#define _W25Q64_H
//===========================================


#define TFE_BIT  (1<<0)  //tranfer fifo empty,1 empty
#define TNF_BIT  (1<<1)  //tranfer fifo not full,0 full,1 not empty
#define RNF_BIT  (1<<2)  //receive not empty,0 empty,
#define RFF_BIT  (1<<3)  //receive full,1 full
#define BSY_BIT  (1<<4)  //busy,1 busy




//===========================================================================

/*   instruction set table 1(standard instructions)  */
#define CMD1_WRITEENABLE            0x06    /* write enable */
#define CMD1_VSR_WRITEENABLE        0x50    /* volatile SR write enable*/
#define CMD1_WRITEDISABLE           0x04    /* write disable */
#define CMD1_READ_SR_1              0x05    /* read status register-1*/
#define CMD1_READ_SR_2              0x35    /* read status register-2*/
#define CMD1_WRITE_SR               0x01    /* write status register */
#define CMD1_PAGE_PROGRAM           0x02    /* page program */
#define CMD1_SECTOR_ERASE_4K        0x20    /* sector erase 4K */
#define CMD1_BLOCK_ERASE_32K        0x52    /* block erase 32K */
#define CMD1_BLOCK_ERASE_64K        0xD8    /* block erase 64K */
#define CMD1_CHIP_ERASE             0xC7    /* chip erase */
#define CMD1_ERASE_PROGRAM_SUSPEND  0x75    /* erase/program suspend */
#define CMD1_ERASE_PROGRAM_RESUME   0x7A    /* erase/program resume */
#define CMD1_POWER_DOWN             0xB9    /* power down */
#define CMD1_READ_DATA              0x03    /* read data  */
#define CMD1_FAST_READ              0x0B    /* fast read */
#define CMD1_RELEASE_POWERDOWN_ID   0xAB    /* release powerdown/ID */
#define CMD1_MANU_DEVICE_ID         0x90    /* manufacturer/Device ID */
#define CMD1_JEDEC_ID               0x9F    /* JEDEC ID*/
#define CMD1_READ_UNIQUE_ID         0x4B    /* read unique ID */
#define CMD1_SFDF_REG               0x5A    /* read SFDF register */
#define CMD1_ERASE_SECURITY_REG     0x44    /* erase security register */
#define CMD1_PROGRAM_SECURITY_REG   0x42    /*program security register */
#define CMD1_READ_SECURITY_REG      0x48    /* read security register */
#define CMD1_ENABLE_QPI             0x38    /* enable QPI */
#define CMD1_ENABLE_RESET           0x66    /* enable reset */
#define CMD1_RESET                  0x99    /* reset */


/*   instruction set table 2(Dual SPI instructions)  */
#define CMD2_FASTREAD_DUALOUT       0x3B      /* fast read dual output   */
#define CMD2_FASTREDA_DUALIO        0xBB      /* fast read dual I/O    */
#define CMD2_MANU_DEVICEID_BYDUALIO 0x92      /* manufacturer/Device ID by Dual I/O   */

/*   instruction set table 3(Quad SPI instructions)  */
#define CMD3_QUAD_PAGE_PRO          0x32  /* quad page program   */
#define CMD3_FASTREAD_QUADOUT       0x6B  /* fast read quad output   */
#define CMD3_FASTREAD_QUADIO        0xEB  /* fast read quad I/O   */
#define CMD3_WORDREAD_QUADIO        0xE7  /* word read quad I/O   */
#define CMD3_OCTAL_WORDREAD_QUADIO  0xE3  /* octal word read quad I/O   */
#define CMD3_SET_BURST_WRAP         0x77  /* set burset with wrap   */
#define CMD3_MANU_DEVICEID_QUADIO   0x94  /* manufacture/device id by quad I/O   */


/*   instruction set table 4(QPI instructions)  */
//#define CMD4_

//===========================================================================


/* local public functions*/


static void SPI_WR_HIGH(void);
static void SPI_WR_LOW(void);
static void SPI_HOLD_HIGH(void);
static void SPI_HOLD_LOW(void);
static void SPI_CS_HIGH(void);
static void SPI_CS_LOW(void);
void ExitNoInt(void);
void EnterNoInt(void);
static void SPI_Flash_Send_1Cmd(uint8 cmd);
static void SPI_Flash_Write_Enable(void);
static void SPI_Flash_Write_Disable(void);
static void SPI_Flash_Vo_SR_WriteEnable(void);
uint8 SPI_Flash_Read_Status_Reg1(void);
uint8 SPI_Flash_Read_Status_Reg2(void);
void SPI_Flash_Write_Status_Reg(uint16 cmd);
void SPI_Flash_Page_Program(uint32 address,
                            uint8* data,
                            uint16 len);
void SPI_Flash_Sector_Erase(uint32 address);
void SPI_Flash_Block_Erase32K(uint32 address);
void SPI_Flash_Block_Erase64K(uint32 address);
void SPI_Flash_Chip_Erase(void);

//#define EnterNoInt() _EnterNoInt()

//#define ExitNoInt() _ExitNoInt()


extern void SPI0_init(void);
extern uint8 SPISendByte(uint8 cdata);
extern void WriteEnable(void);
extern void WriteDisable(void);
extern void ReadUniqueID(uint8 *databuffer);
//extern void ReadDeviceID(uint8 *databuffer);
extern void Sector_4K_Erase(uint32);
extern void Sector_32K_Erase(uint32 address);
extern void Sector_64K_Erase(uint32 address);
extern void FlashProgram(uint8 *databuffer,uint16 datasize,uint32 address) ;
extern void M25P80_Write_1Byte(uint32 addr , uint8 data);
extern void ReadFlash(uint8 *databuffer,uint16 datasize,uint32 address);

extern uint8 CheckData(uint8 *DataBuffer, uint32 DataAddr, uint16 DataSize);

extern uint16 SPI_Flash_Read_MANU_DEVICE_ID(void);
extern uint8  SPI_Flash_ReadUniqueID(void);
extern uint32 SPI_Flash_Read_JEDECID(void);
extern uint8  SPI_Flash_Read_ReleasePowerDownID(void);
extern uint8  SPI_Flash_Read_Data(uint32 address);
extern uint8  SPI_Flash_Fast_Read(uint32 address);

//
extern uint8 ReadFlash_1Byte(uint32 addr);


//////////////////new things//////////////
extern void ReadManufactDeviceID_90h_W25Q(void);

extern void ChipErase(void);
//===========================================================================

#endif
