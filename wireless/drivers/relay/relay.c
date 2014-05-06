#include "relay.h"


//��ˮ�֣����ϣ��������
void Relay_Init(void)
{
    //Fire_relay--p0.0
    PINSEL0 &=~(1<<0);//fun 0:gpio
//Fault_relay--p0.1
    PINSEL0 &=~(1<<1);//fun 0:gpio

    FIO0DIR |= (1<<0) | (1<<1);//dir:output
    FIO0CLR |= (1<<0) | (1<<1);	//voltage:low
}
void Fire_Relay_On(void)
{
    FIO0SET |= (1<<0);
}
void Fire_Relay_Off(void)
{
    FIO0CLR |= (1<<0);
}
void Fault_Relay_On(void)
{
    FIO0SET |= (1<<1);
}
void Fault_Relay_Off(void)
{
    FIO0CLR |= (1<<1);
}
