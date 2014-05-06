#ifndef TIMEDEF_H
#define TIMEDEF_H

//����ʱ��

#include "includeall.h"

#ifdef EXTERN_TIMEDEF
#define EXT_TIMEDEF
#else
#define EXT_TIMEDEF extern
#endif



/*******************************************************************/
/******************       ȫ�ֳ�������?    *********************/
/*******************************************************************/
//constant
#define  cTime0_2ms     0    //ͬ��
#define  cTime0_5ms     1    //
#define  cTime0_600us   2    //���ݲ���
#define  cTime0_8ms     3    //

#define  cCMaxTime0Def   4    //


#define  cSystemFrequency   100
#define  cSystemTimeBit     2500

#define  cTime0V_2ms     cSystemTimeBit*20
#define  cTime0V_5ms     cSystemTimeBit*50
#define  cTime0V_600us   cSystemTimeBit*6
#define  cTime0V_8ms     cSystemTimeBit*80
#define  cTime0V_20ms     cSystemTimeBit*200


#define  cTimeUnit   200

#define  cTime2ms     (2000/cTimeUnit)
#define  cTime10ms    (10000/cTimeUnit)
#define  cTime14ms    (14000/cTimeUnit)
#define  cTime18ms    (18000/cTimeUnit)
#define  cTime50ms    (50000/cTimeUnit)


/*******************************************************************/
/******************       ���ݽṹ����?    *********************/
/*******************************************************************/
typedef union type_WaitToRun{
    uint32 Word;
    struct
    {
        volatile uint32 b2ms:1;//wait 2ms arrived,must be volatile
        uint32 b20ms:1;//keyboard
        uint32 b100ms:1;//lcd display
        uint32 b500ms:1;//rtc clock
    }Flag;


}WaitToRun;



/*******************************************************************/
/****************     ���г�Ա����,����������     ******************/
/*******************************************************************/


EXT_TIMEDEF  uint32   Get_CTime0Def(void);
EXT_TIMEDEF  void     Set_CTime0Def(uint32 vTimeId);
EXT_TIMEDEF  uint32   Sel_CTime0Def(uint8 vTimer);
EXT_TIMEDEF  uint32   Get_Timer_100us(void);
EXT_TIMEDEF  uint32   Get_Timer_200us(void);
EXT_TIMEDEF  uint32   Get_Timer_600us(void);
EXT_TIMEDEF  uint32   Get_Timer_2ms(void);
EXT_TIMEDEF  uint32   Get_Timer_5ms(void);
EXT_TIMEDEF  uint32   Get_Timer_8ms(void);
EXT_TIMEDEF  uint32   Get_Timer_10ms(void);
EXT_TIMEDEF  uint32   Get_Timer_20ms(void);

//�����½���ʱ��
EXT_TIMEDEF void AddTwoFallEdgeCounter(void);
EXT_TIMEDEF void ClrTwoFallEdgeCounter(void);
EXT_TIMEDEF uint32 GetTwoFallEdgeCounter(void);
//������ʱ��
EXT_TIMEDEF void AddRisedgeCounter(void);
EXT_TIMEDEF void ClrRisedgeCounter(void);
EXT_TIMEDEF uint32 GetRisedgeCounter(void);
//�ȴ�2ms //2ms wait state
EXT_TIMEDEF void AddWait2msCounter(void);
EXT_TIMEDEF void ClrWait2msCounter(void);
EXT_TIMEDEF uint32 GetWait2msCounter(void);
EXT_TIMEDEF uint8 Is2msArrived(void);
EXT_TIMEDEF void Enable2ms(void);
EXT_TIMEDEF void Disable2ms(void);
EXT_TIMEDEF uint8 Get2msState(void);
//2ms arrived flag
EXT_TIMEDEF void Set2msArrived(void);
EXT_TIMEDEF uint32 Get2msArrived(void);
EXT_TIMEDEF void Clr2msArrived(void);


/*******************************************************************/
/********************* ˽�г�Ա����,����������    *******************/
/*******************************************************************/
//Private:
//#define CTimeDef_C
#ifdef  CTimeDef_C

uint32  vCurTime0Def=0;
volatile uint32 vTimer0Counter=0;//�����½��س��ȣ�ͬ����ȡ
volatile uint32 vTimerRisingCounter=0;//��¼�����س��ȣ������ȡ
volatile uint32 vTimer0Wait2msCounter=0;//�ȴ�2ms,�ȴ���������
volatile uint8 vWait2msState=0;//enable or disable wait 2ms
static  uint32  m_Time0Def[cCMaxTime0Def]={cTime0V_2ms,cTime0V_5ms,cTime0V_600us,cTime0V_8ms};

volatile WaitToRun vWaittoRun;
#endif

#endif // TIMEDEF_H
