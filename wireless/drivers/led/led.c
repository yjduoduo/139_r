#include "led.h"


void led_init(void)
{
    Led_Run_Init();
    Led_Silence_Init();
    Led_Wireless_Init();
    Led_Fault_Init();
    Led_Fire_Init();

    Led_Run_Off();
    Led_Silence_Off();
    Led_Wireless_Off();
    Led_Fault_Off();
    Led_Fire_Off();
}

void led_on(void)
{
    Led_Run_On();
    Led_Silence_On();
    Led_Wireless_On();
    Led_Fault_On();
    Led_Fire_On();
}
void Led_Off(void)
{
    Led_Run_Off();
    Led_Silence_Off();
    Led_Wireless_Off();
    Led_Fault_Off();
    Led_Fire_Off();
}
//运行p0.15
void Led_Run_Init(void)
{
    //gpio,output,high
    PINSEL0 &=~(1<<30);
    FIO0DIR |= (1<<15);
    FIO0SET |= (1<<15);
}
void Led_Run_On(void)
{
    FIO0SET |= (1<<15);
}
void Led_Run_Off(void)
{
    FIO0CLR |= (1<<15);
}
//静音p0.16
void Led_Silence_Init(void)
{
    //gpio,output,high
    PINSEL1 &= ~(1<<0);//16bit gpio
    FIO0DIR |= (1<<16);//16bit output
    FIO0SET |= (1<<16);//16bit high
}
void Led_Silence_On(void)
{
    FIO0SET |= (1<<16);
}
void Led_Silence_Off(void)
{
    FIO0CLR |= (1<<16);
}
//通讯p2.4
void Led_Wireless_Init(void)
{
    PINSEL4 &=~(1<8);
    FIO2DIR |= (1<<4);
    FIO2SET |= (1<<4);
}
void Led_Wireless_On(void)
{
    FIO2SET |= (1<<4);
}
void Led_Wireless_Off(void)
{
    FIO2CLR |= (1<<4);
}

//故障p2.5
void Led_Fault_Init(void)
{
    PINSEL4 &=~(1<10);
    FIO2DIR |= (1<<5);
    FIO2SET |= (1<<5);
}
void Led_Fault_On(void)
{
    FIO2SET |= (1<<5);
}
void Led_Fault_Off(void)
{
    FIO2CLR |= (1<<5);
}

//火警p2.6
void Led_Fire_Init(void)
{
    PINSEL4 &=~(1<12);
    FIO2DIR |= (1<<6);
    FIO2SET |= (1<<6);
}
void Led_Fire_On(void)
{
    FIO2SET |= (1<<6);
}
void Led_Fire_Off(void)
{
    FIO2CLR |= (1<<6);
}

