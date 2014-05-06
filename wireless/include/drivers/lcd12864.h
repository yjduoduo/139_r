#ifndef LCD12864_H
#define LCD12864_H

#include "includeall.h"

#ifdef EXTERN_LCD12864
#define EXT_LCD12864
#else
#define EXT_LCD12864 extern
#endif


//LCD12864
#define LCD_DE() FIO1SET |= 1<<18    /*写数据*/
#define LCD_IE() FIO1CLR |= 1<<18    /*写命令*/
#define LCD_RE() FIO1SET |= 1<<19    /*读使能*/
#define LCD_WE() FIO1CLR |= 1<<19   /*写使能*/
#define LCD_EH() FIO1SET |= 1<<20    /*写高*/
#define LCD_EL() FIO1CLR |= 1<<20    /*写低*/
//LCD12864
#define LCDSTARROW 0xC0    /*???????*/
#define LCDPAGE    0xB8    /*?????*/
#define LCDLINE    0x40    /*?????*/
/////////////////////////////////////////////////////////////////////////////

EXT_LCD12864 void DelayMs(uint32 Time);   /*延时1MS*/
EXT_LCD12864 void DATAout(uint8 j);
EXT_LCD12864 void CheckState(void);  /*状态检查，LCD是否忙*/
EXT_LCD12864 void SendCommandToLCD(uint8 com); /*写命令到LCD中*/
EXT_LCD12864 void SetLine(uint8 page);	/*设置页 0xb8是页的首地址*/
 /*设定显示开始行，0xc0是行的首地址*/
EXT_LCD12864 void SetStartLine(uint8 startline);
/*设定列地址--Y 0-63 ，0x40是列的首地址*/
EXT_LCD12864 void SetColumn(uint8 column);
 /*开关显示，0x3f是开显示，0x3e是关显示*/
EXT_LCD12864 void SetOnOff(uint8 onoff);
/*写显示数据 */
EXT_LCD12864 void WriteByte(uint8 dat);
/*选择屏幕screen: 0-全屏,1-左屏,2-右屏*/
EXT_LCD12864 void SelectScreen(uint8 screen);
 /*清屏screen: 0-全屏,1-左屏,2-右屏*/
EXT_LCD12864 void ClearScreen(uint8  screen);
EXT_LCD12864 void Clear16Screen(uint8  screen);
/*短延时程序*/
EXT_LCD12864 void delay(uint8  z);
/*长延时程序*/
EXT_LCD12864 void delay_long (uint32 ulTime);
/*初始化LCD*/
EXT_LCD12864 void lcd_init(void );
/*显示全角汉字*///选屏参数，page选页参数，column选列参数，number选第几汉字输出
EXT_LCD12864 void Display(uint8  ss,uint8  page,uint8  column,uint32  number);
EXT_LCD12864 void DisplayBlack(uint8  ss,uint8  page,uint8  column,uint32  number);
EXT_LCD12864 void Display12by12(uint8  ss,uint8  page,uint8  column,uint8  number);
//选屏参数，page选页参数，column选列参数，number选第几汉字输出
EXT_LCD12864 void Display1(uint8  ss,uint8  page,uint8  column,uint8  number);
//选屏参数，page选页参数，column选列参数，number选第几汉字输出
EXT_LCD12864 void Displaynumber(uint8  ss,uint8  page,uint8  column,uint8  number);
EXT_LCD12864 void IOint(void);
//void Start_Menu(void);
EXT_LCD12864 void DisplaynumberBlack(uint8  ss,uint8 page,uint8  column,uint8  number);
EXT_LCD12864 void WriteBlackByte(uint8 dat);
EXT_LCD12864 void WriteBlue(uint8 screen,uint8 line,uint8 col,uint8 row);

EXT_LCD12864 void DisplayJBHZK(uint8  ss,uint8  page,uint8  column,uint16 xHZcode);
EXT_LCD12864 void DisplayJBHZKBlack(uint8  ss,uint8  page,uint8  column,uint16 xHZcode);






#endif // LCD12864_H
