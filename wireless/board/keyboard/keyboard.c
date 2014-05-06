#define _VAR_C_KEYBOARD
#include "keyboard.h"


#define KEY_P10  (FIO0PIN&(1 << 10))//up
#define KEY_P11  (FIO0PIN&(1 << 11))//down
#define KEY_P25  (FIO0PIN&(1 << 25))//back
#define KEY_P26  (FIO0PIN&(1 << 26))//silence
#define KEY_P29  (FIO0PIN&(1 << 29))//sure
#define KEY_P30  (FIO0PIN&(1 << 30))//return


#define KEY_UP          KEY_P30
#define KEY_DOWN        KEY_P29
#define KEY_SILENCE     KEY_P11
#define KEY_BACK        KEY_P26
#define KEY_OK          KEY_P10
#define KEY_RETURN      KEY_P25
//去抖time
#define KEYDELAYTIME 15 //40--10ms  40/3 /2=13.3/2=7

//typedef union type_scan_key{
//    uint32 Word;
//    struct{
//        uint32 keym:3;
//        uint32 counterpos:3;
//        uint32 timer:2;
//        void (*fun)(void);
//    }Bit;


//}t_scan_key;
//#define TIMER2_USED 2

//t_scan_key m_t_scan_key[]={
//    {KEY_UP,4,TIMER2_USED,fun_default},
//    {KEY_DOWN,5,TIMER2_USED,fun_default},
//    {KEY_SILENCE,1,TIMER2_USED,fun_silence},
//    {KEY_BACK,3,TIMER2_USED,fun_default},
//    {KEY_OK,0,TIMER2_USED,fun_default},
//    {KEY_RETURN,2,TIMER2_USED,fun_return},
//};
//void fun_default(void)
//{
//    OpenLCD();
//}

//void fun_silence(void)
//{
//    BEEPOff();
//    SetAlarmFlag(0,0);
//    if(GetDisplay_alarm_flag())
//        Led_Silence_On();
//    OpenLCD();
//}
//void fun_return(void)
//{
//    if(!GetDisplay_alarm_flag())
//        Led_Silence_Off();
//    OpenLCD();
//}





void Scan_Key(void)
{
//    uint8 val=0;
//    for(val=0;val<ARRAYSIZE(m_t_scan_key);val++)
//    {
//        if(!m_t_scan_key[val].Bit.keym)
//        {
//            Delay1Ms(KEYDELAYTIME);
//            if(!m_t_scan_key[val].Bit.keym)
//            {
//                vKeyCounter[m_t_scan_key[val].Bit.counterpos]++;
//                if(vKeyCounter[0] >= 1)
//                {
//                    disable_timer(m_t_scan_key[val].Bit.timer);
//                    m_t_scan_key[val].Bit.fun();
//                    Delay1Ms(KEYDELAYTIME); //去抖
//                    return;
//                }
//            }

//        }
//    }
//    return;





    if(!KEY_OK) //确定键
    {
        Delay1Ms(KEYDELAYTIME);
        if(!KEY_OK)
        {
            vKeyCounter[0]++;
            if(vKeyCounter[0] >= 1)
            {
                disable_timer(2);

            }
            OpenLCD();
            Delay1Ms(KEYDELAYTIME); //去抖
            return;


        }

    }
    else
    {
        vKeyCounter[0] = 0;
    }
    if(!KEY_SILENCE)//静音键
    {
        Delay1Ms(KEYDELAYTIME);
        if(!KEY_SILENCE)
        {
            vKeyCounter[1]++;
            if(vKeyCounter[1] >= 1)
            {
                disable_timer(2);

            }
            BEEPOff();
            SetAlarmFlag(0,0);
            if(GetDisplay_alarm_flag())
                Led_Silence_On();
            OpenLCD();
            Delay1Ms(KEYDELAYTIME); //去抖
            return;


        }
    }
    else
    {
        vKeyCounter[1] = 0;
    }
    if(!KEY_RETURN)//返回键
    {
        Delay1Ms(KEYDELAYTIME);
        if(!KEY_RETURN)
        {
            vKeyCounter[2]++;
            if(vKeyCounter[2] >= 1)
            {
                disable_timer(2);

            }
            if(!GetDisplay_alarm_flag())
                Led_Silence_Off();
            OpenLCD();
            Delay1Ms(KEYDELAYTIME); //去抖
            return;


        }

    }
    else
    {
        vKeyCounter[2] = 0;
    }
    if(!KEY_BACK)//回退键
    {
        Delay1Ms(KEYDELAYTIME);
        if(!KEY_BACK)
        {
            vKeyCounter[3]++;
            if(vKeyCounter[3] >= 1)
            {
                disable_timer(2);

            }
            OpenLCD();
            Delay1Ms(KEYDELAYTIME); //去抖
            return;


        }
    }
    else
    {
        vKeyCounter[3] = 0;
    }
    if(!KEY_UP)//向上键
    {
        Delay1Ms(KEYDELAYTIME);
        if(!KEY_UP)
        {
            vKeyCounter[4]++;
            if(vKeyCounter[4] >= 1)
            {
                disable_timer(2);

            }
            OpenLCD();
            Delay1Ms(KEYDELAYTIME); //去抖
            return;


        }
    }
    else
    {
        vKeyCounter[4] = 0;
    }
    if(!KEY_DOWN)//向下键
    {
        Delay1Ms(KEYDELAYTIME);
        if(!KEY_DOWN)
        {
            vKeyCounter[5]++;
            if(vKeyCounter[5] >= 1)
            {
                disable_timer(2);

            }
            OpenLCD();
            Delay1Ms(KEYDELAYTIME); //去抖
            return;


        }
    }
    else
    {
        vKeyCounter[5] = 0;
    }
}
uint16 CGet_KeyValue(void)
{
    if(vKeyCounter[0] >= 1)
    {
        if(KEY_OK)
        {
            enable_timer(2);
            vKeyCounter[0] = 0;

            return KEY_Sure;
        }
    }
    if(vKeyCounter[1] >= 1)
    {
        if(KEY_SILENCE)
        {
            enable_timer(2);
            vKeyCounter[1] = 0;
            BEEPOff();
            PWM1_Stop();
            CSetAlarmFlag(0,0);

            return KEY_Silence;
        }
    }
    if(vKeyCounter[2] >= 1)
    {
        if(KEY_RETURN)
        {
            enable_timer(2);
            vKeyCounter[2] = 0;
            return KEY_Return;
        }
    }
    if(vKeyCounter[3] >= 1)
    {
        if(KEY_BACK)
        {
            enable_timer(2);
            vKeyCounter[3] = 0;

            if(GetPasswordFlag())
                ClrBackValue();
            else
                vBackValue++;
            return KEY_Back;
        }
    }
    if(vKeyCounter[4] >= 1)
    {
        if(KEY_UP)
        {
            enable_timer(2);
            vKeyCounter[4] = 0;
            return KEY_Up;
        }
    }
    if(vKeyCounter[5] >= 1)
    {
        if(KEY_DOWN)
        {
            enable_timer(2);
            vKeyCounter[5] = 0;
            return KEY_Down;
        }
    }
    return 0xff;
}
