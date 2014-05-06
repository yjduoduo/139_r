#define DELAY_VAR
#include "delay.h"





void SysTick_Handler(void)
{
    msTicks++;                        /* increment counter necessary in Delay() */
}
void DelayUs2x(unsigned char t)
{
    while(--t);
}
void Delay1Ms(uint32 t)
{
   while(t--)
   {
       //¥Û÷¬—” ±1mS
       DelayUs2x(245);
       DelayUs2x(245);
   }

}
