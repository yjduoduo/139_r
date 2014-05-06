#include "extint.h"

#define PIN23 (0x1<<23)
#define PIN24 (0x1<<24)


void pin023_extint_init(void)
{
    PINSEL1 &=~(0x03<<14);//p0.23ѡ��ΪGPIO
    FIO0DIR  &= (~ (0x01<<23)) ;  // P0.23����Ϊ����
    IO0IntEnR |=  (0x01<<24);    //�������ж�P0.24
    IO0IntEnF |=  (0x01<<23);    //�½����ж�P0.23
}
void pin024_extint_init(void)
{
    PINSEL1 &=~(0x03<<16);//p0.24ѡ��ΪGPIO
    FIO0DIR  &= (~ (0x01<<24)) ;  // P0.24����Ϊ����
    IO0IntEnF |= (0x01<<24);    //�½����ж�P0.24
    IO0IntEnR |= (0x01<<24);   //�������ж�P0.24
}
void extint3_enable(void)
{
    NVIC_EnableIRQ(EINT3_IRQn);//�ж�ʹ��
    NVIC_SetPriority(EINT3_IRQn, PRIO_ZERO); //�ж����ȼ�
}


/*********************************************************************************************************
** Function name:       Eint3_Init
** Descriptions:        �ⲿ�ж�3��ʼ���������ش���
*********************************************************************************************************/
void extint3_init(void)
{
    pin024_extint_init();
    extint3_enable();
}



void pin211_extint_init(void)
{
    PINSEL4 |= (1 << 22);//����p2.11 �ⲿ�ж�1

    EXTMODE  |= 1 << 0;          /* ���ô�����ʽ     ENIT1���ش���  */
    //    EXTMODE &= ~(1<<1);            /* ���ô�����ʽ     ENIT1��ƽ����  */
    EXTPOLAR &= ~(1 << 1);	///* EINT1 is falling edge

}
void extint1_enable(void)
{
    NVIC_EnableIRQ(EINT1_IRQn);//�ж�ʹ��
    NVIC_SetPriority(EINT1_IRQn, PRIO_FIVE); //�ж����ȼ�
}



/*********************************************************************************************************
** Function name:       Eint1_Init
** Descriptions:        �ⲿ�ж�1��ʼ�����½��ش���
�ж�1������RTC_INT
*********************************************************************************************************/
void extint1_init(void)
{
    pin211_extint_init();
    extint1_enable();
}




