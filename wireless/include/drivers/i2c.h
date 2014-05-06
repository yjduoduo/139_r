#ifndef I2C_H
#define I2C_H

#include "includeall.h"


#ifdef EXTERN_I2C
#define EXT_I2C
#else
#define EXT_I2C extern
#endif


#define ONE_BYTE_SUBA   1
#define TWO_BYTE_SUBA   2
#define X_ADD_8_SUBA    3


#define I2C0CONCLR_AAC        (0x1<<2)  /* I2C Control clear Register */
#define I2C0CONCLR_SIC        (0x1<<3)
#define I2C0CONCLR_STAC       (0x1<<5)
#define I2C0CONCLR_I2ENC      (0x1<<6)

#define I2C0CONSET_I2EN       (0x1<<6)  /* I2C Control Set Register */
#define I2C0CONSET_AA         (0x1<<2)
#define I2C0CONSET_SI         (0x1<<3)
#define I2C0CONSET_STO        (0x1<<4)
#define I2C0CONSET_STA        (0x1<<5)



#define FOSC                        12000000                            /*  振荡器频率                  */

#define FCCLK                      (FOSC  * 8)                          /*  主时钟频率<=100Mhz          */
/*  FOSC的整数倍                */
#define FCCO                       (FCCLK * 3)                          /*  PLL频率(275Mhz~550Mhz)      */
/*  与FCCLK相同，或是其的偶数倍 */
#define FPCLK                      (FCCLK / 4)                          /*  外设时钟频率,FCCLK的1/2、1/4*/
/*  或与FCCLK相同  */




//public function declearation

EXT_I2C void  i2c0_init(uint32 ulFi2c);
EXT_I2C void i2c0_disable(void);
EXT_I2C void I2CIntStart(void);
EXT_I2C uint8 IRcvByte(uint8 sla, uint8 *dat);
EXT_I2C uint8 ISendByte(uint8 sla, uint8 dat);
EXT_I2C uint8 I2C_ReadNByte (uint8 sla, uint32 suba_type, uint32 suba, uint8 *s, uint32 num);
EXT_I2C uint8 I2C_WriteNByte(uint8 sla, uint8 suba_type, uint32 suba, uint8 *s, uint32 num);



























#endif // I2C_H
