#ifndef LCD12864_H
#define LCD12864_H

#include "includeall.h"

#ifdef EXTERN_LCD12864
#define EXT_LCD12864
#else
#define EXT_LCD12864 extern
#endif


//LCD12864
#define LCD_DE() FIO1SET |= 1<<18    /*д����*/
#define LCD_IE() FIO1CLR |= 1<<18    /*д����*/
#define LCD_RE() FIO1SET |= 1<<19    /*��ʹ��*/
#define LCD_WE() FIO1CLR |= 1<<19   /*дʹ��*/
#define LCD_EH() FIO1SET |= 1<<20    /*д��*/
#define LCD_EL() FIO1CLR |= 1<<20    /*д��*/
//LCD12864
#define LCDSTARROW 0xC0    /*???????*/
#define LCDPAGE    0xB8    /*?????*/
#define LCDLINE    0x40    /*?????*/
/////////////////////////////////////////////////////////////////////////////

EXT_LCD12864 void DelayMs(uint32 Time);   /*��ʱ1MS*/
EXT_LCD12864 void DATAout(uint8 j);
EXT_LCD12864 void CheckState(void);  /*״̬��飬LCD�Ƿ�æ*/
EXT_LCD12864 void SendCommandToLCD(uint8 com); /*д���LCD��*/
EXT_LCD12864 void SetLine(uint8 page);	/*����ҳ 0xb8��ҳ���׵�ַ*/
 /*�趨��ʾ��ʼ�У�0xc0���е��׵�ַ*/
EXT_LCD12864 void SetStartLine(uint8 startline);
/*�趨�е�ַ--Y 0-63 ��0x40���е��׵�ַ*/
EXT_LCD12864 void SetColumn(uint8 column);
 /*������ʾ��0x3f�ǿ���ʾ��0x3e�ǹ���ʾ*/
EXT_LCD12864 void SetOnOff(uint8 onoff);
/*д��ʾ���� */
EXT_LCD12864 void WriteByte(uint8 dat);
/*ѡ����Ļscreen: 0-ȫ��,1-����,2-����*/
EXT_LCD12864 void SelectScreen(uint8 screen);
 /*����screen: 0-ȫ��,1-����,2-����*/
EXT_LCD12864 void ClearScreen(uint8  screen);
EXT_LCD12864 void Clear16Screen(uint8  screen);
/*����ʱ����*/
EXT_LCD12864 void delay(uint8  z);
/*����ʱ����*/
EXT_LCD12864 void delay_long (uint32 ulTime);
/*��ʼ��LCD*/
EXT_LCD12864 void lcd_init(void );
/*��ʾȫ�Ǻ���*///ѡ��������pageѡҳ������columnѡ�в�����numberѡ�ڼ��������
EXT_LCD12864 void Display(uint8  ss,uint8  page,uint8  column,uint32  number);
EXT_LCD12864 void DisplayBlack(uint8  ss,uint8  page,uint8  column,uint32  number);
EXT_LCD12864 void Display12by12(uint8  ss,uint8  page,uint8  column,uint8  number);
//ѡ��������pageѡҳ������columnѡ�в�����numberѡ�ڼ��������
EXT_LCD12864 void Display1(uint8  ss,uint8  page,uint8  column,uint8  number);
//ѡ��������pageѡҳ������columnѡ�в�����numberѡ�ڼ��������
EXT_LCD12864 void Displaynumber(uint8  ss,uint8  page,uint8  column,uint8  number);
EXT_LCD12864 void IOint(void);
//void Start_Menu(void);
EXT_LCD12864 void DisplaynumberBlack(uint8  ss,uint8 page,uint8  column,uint8  number);
EXT_LCD12864 void WriteBlackByte(uint8 dat);
EXT_LCD12864 void WriteBlue(uint8 screen,uint8 line,uint8 col,uint8 row);

EXT_LCD12864 void DisplayJBHZK(uint8  ss,uint8  page,uint8  column,uint16 xHZcode);
EXT_LCD12864 void DisplayJBHZKBlack(uint8  ss,uint8  page,uint8  column,uint16 xHZcode);






#endif // LCD12864_H
