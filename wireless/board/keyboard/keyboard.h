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
    uint8	key_back;    //���˼�
    uint8 key_up;      //���ϼ�
    uint8 key_down;    //���¼�
    uint8 key_sure;    //ȷ�ϼ�
    uint8 key_return;  //���ؼ�
    uint8 key_silence; //������
}TdKeyValue,*PdKeyValue;

uint32 vKeyCounter[6] = {0};
uint8 vBackValue=0;



#endif

#endif // KEYBOARD_H
