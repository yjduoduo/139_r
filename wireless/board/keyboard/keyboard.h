#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "includeall.h"
#include "inc_all_hardware.h"

#ifdef EXTERN_KEYBOARD
#define EXT_KEYBOARD
#else
#define EXT_KEYBOARD extern
#endif




//private
#ifdef _VAR_C_KEYBOARD

typedef struct KeyValue
{
    uint8	key_back;    //回退键
    uint8 key_up;      //向上键
    uint8 key_down;    //向下键
    uint8 key_sure;    //确认键
    uint8 key_return;  //返回键
    uint8 key_silence; //消音键
}TdKeyValue,*PdKeyValue;

uint32 vKeyCounter[6] = {0};
uint8 vBackValue=0;



#endif

#endif // KEYBOARD_H
