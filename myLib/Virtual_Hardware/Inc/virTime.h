/**
*********************************************************************
*********
* @project_name ：car0
* @file ：BasevirTime.h
* @author ：zen3
* @brief ：这个头文件定义了抽象类virTime，作为定时器和PWM功能的接口。
* @attention ：无
* @date ：2023/11/9
*********************************************************************
*********
*/

#ifndef CAR0_VIRTIME_H
#define CAR0_VIRTIME_H
#define   MAXTIMNUM 14
#include "Resources.h"

typedef void (*callback_t)(void);
typedef void (*callback_with_arg_t)(void*);
struct TimeExitValue{
    callback_with_arg_t TimeExit[MAXTIMNUM];
    callback_with_arg_t TimePWMExit[MAXTIMNUM];
    void* arg[MAXTIMNUM];
};
struct virTimeValue{
    TIM_HandleTypeDef TIMEList[MAXTIMNUM];//全局定时器句柄
    uint8_t TIMEx_Channel[MAXTIMNUM];
    uint8_t TIMEx_IRQn[MAXTIMNUM];
};
extern uint8_t OnceFlag[MAXTIMNUM];
extern TimeExitValue ExitValue;
extern virTimeValue BaseTimeValue;
//extern virTimeValue UniversalTimeValue;
//extern virTimeValue AdvancedTimeValue;
class virTime {
public:
    virtual uint32_t timerGreatPsc(Timer_enum timer, uint32_t arr,
                                   uint8_t PreemptPriority, uint8_t SubPriority) =0;
    virtual void timerStartOnce(Timer_enum timer)=0;
    virtual void timerStartPeriodic(Timer_enum timer)=0;
    virtual void timerStop(Timer_enum timer)=0;
    virtual void timerDelete(Timer_enum timer)=0;
};
#endif