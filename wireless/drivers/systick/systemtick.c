/*************************************************************************************	  
*	main.c:  the main file 
*	NXP --> LPC1768
*
*   
*	Author	:	light					
*	Date	:	2012-4-16  
*
***************************************************************************************/

#include<LPC17XX.h>


volatile uint32_t msTicks;                            /* counts 1ms timeTicks */
/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
/********************************************************************************
** Descriptions			：SysTick interrupt handle
**
** parameters			：None
** Returned value		：None
*********************************************************************************/
void SysTick_Handler(void) 
{
	msTicks++;                        /* increment counter necessary in Delay() */
}

/*------------------------------------------------------------------------------
  delays number of tick Systicks (happens every 1 ms)
 *------------------------------------------------------------------------------*/
__INLINE static void Delay (uint32_t dlyTicks) 
{
	uint32_t curTicks;	  

	curTicks = msTicks;	    // 获取当前值

	while ((msTicks - curTicks) < dlyTicks);	  //等待，即延时
}

/********************************************************************************
** Descriptions			：Function that initializes LEDs
**
** parameters			：None
** Returned value		：None
*********************************************************************************/
void DelayMs(unsigned int m)
{
	int i,j;
	for(i=m;i>0;i--)
	{
		for(j=3000;j>0;j--);
	}

}

/********************************************************************************
** Descriptions			：Function that initializes LEDs
**
** parameters			：None
** Returned value		：None
*********************************************************************************/
void LedInit(void) 
{
	// PINSEL4,PINSEL5 设定P2.0 -- P2.32 端口功能（00，01,10,11）
	LPC_PINCON->PINSEL4 = 0XFC000000;			// p2.0--p2.13设置为IO 

	LPC_PINCON->PINMODE4 = 0XFC000000;			// p2.0--p2.13设置为上拉电阻使能

	LPC_GPIO2->FIODIR = 0X000000FF;	 		// p2.0--p2.7设置为输出

}

/********************************************************************************
** Descriptions			：Function that LED on
**
** parameters			：n , which led is on
** Returned value		：None
*********************************************************************************/
void LedNOn(unsigned int n)
{
	LPC_GPIO2->FIOSET = (1<<n);		
}
/********************************************************************************
** Descriptions			：Function that LED off
**
** parameters			：n , which led is 0ff
** Returned value		：None
*********************************************************************************/
void LedNOff(unsigned int n)
{
	LPC_GPIO2->FIOCLR = (1<<n);		
}

/*----------------------------------------------------------------------------
  The main Function 
 *----------------------------------------------------------------------------*/
int main(void)
{
	int loc;
	SystemInit();
	LedInit();	  
  	// SysTick定时器初始化
	if (SysTick_Config(0x05F5E100 / 1000))			/* Setup SysTick Timer for 1 msec interrupts  */
    {
		while (1);                                  /* Capture error */
  	}

	while(1)
	{
		for(loc=7;loc>=0;loc--)
		{
			LedNOn(loc);
			Delay(1000);

			LedNOff(loc);
			Delay(1000);
		}


	}

}
