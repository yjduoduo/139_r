#include "extint.h"

#define PIN23 (0x1<<23)
#define PIN24 (0x1<<24)


void pin023_extint_init(void)
{
    PINSEL1 &=~(0x03<<14);//p0.23选择为GPIO
    FIO0DIR  &= (~ (0x01<<23)) ;  // P0.23方向为输入
    IO0IntEnR |=  (0x01<<24);    //上升沿中断P0.24
    IO0IntEnF |=  (0x01<<23);    //下降沿中断P0.23
}
void pin024_extint_init(void)
{
    PINSEL1 &=~(0x03<<16);//p0.24选择为GPIO
    FIO0DIR  &= (~ (0x01<<24)) ;  // P0.24方向为输入
    IO0IntEnF |= (0x01<<24);    //下降沿中断P0.24
    IO0IntEnR |= (0x01<<24);   //上升沿中断P0.24
}
void extint3_enable(void)
{
    NVIC_EnableIRQ(EINT3_IRQn);//中断使能
    NVIC_SetPriority(EINT3_IRQn, PRIO_ZERO); //中断优先级
}


/*********************************************************************************************************
** Function name:       Eint3_Init
** Descriptions:        外部中断3初始化，上升沿触发
*********************************************************************************************************/
void extint3_init(void)
{
    pin024_extint_init();
    extint3_enable();
}



void pin211_extint_init(void)
{
    PINSEL4 |= (1 << 22);//设置p2.11 外部中断1

    EXTMODE  |= 1 << 0;          /* 设置触发方式     ENIT1边沿触发  */
    //    EXTMODE &= ~(1<<1);            /* 设置触发方式     ENIT1电平触发  */
    EXTPOLAR &= ~(1 << 1);	///* EINT1 is falling edge

}
void extint1_enable(void)
{
    NVIC_EnableIRQ(EINT1_IRQn);//中断使能
    NVIC_SetPriority(EINT1_IRQn, PRIO_FIVE); //中断优先级
}



/*********************************************************************************************************
** Function name:       Eint1_Init
** Descriptions:        外部中断1初始化，下降沿触发
中断1用来对RTC_INT
*********************************************************************************************************/
void extint1_init(void)
{
    pin211_extint_init();
    extint1_enable();
}




