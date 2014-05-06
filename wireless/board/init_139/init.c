#include "init.h"
#include "inc_all_hardware.h"
#include "timedef.h"


void hardware_init(void)
{

    /*updates the SystemFrequency variable */
    SystemClockUpdate();
    gpio_init();
    //    UARTInit(0, 2400);	/* baud rate setting */ //send message to phone
    uart0_init(9600);/* baud rate setting */
    uart1_init(9600);/* baud rate setting */

    lcd_init();

    extint1_init();
    extint3_init();//extint3
    i2c0_init(400000);
    timer_all_init(0,Get_Timer_200us());//��ʱ��0����·����
    timer_all_init(1,Get_Timer_20ms());    //��ʱ��1���Լ죬����ʾ
    timer_all_init(2,Get_Timer_10ms());    //��ʱ��2������ɨ��
    ssp1_init();
    led_init();
    Relay_Init();
    //���ư�begin////
    PWM_Init();
    PWM1_Set( PWM_CYCLE, 0 );

}

