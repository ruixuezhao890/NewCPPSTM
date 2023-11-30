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
#include "TimeResources.h"
class virTime {
public:
    virtual uint32_t timerGreatPsc(Timer_enum timer, uint32_t arr,
                                   uint8_t PreemptPriority, uint8_t SubPriority) =0;
    virtual TIM_HandleTypeDef * timerGreatPscNoInit(Timer_enum timer, uint32_t psc, uint32_t arr,
                                                    uint8_t PreemptPriority, uint8_t SubPriority) =0;
    virtual void timerStartOnce(Timer_enum timer)=0;
    virtual void timerStartPeriodic(Timer_enum timer)=0;
    virtual void timerStop(Timer_enum timer)=0;
    virtual void timerDelete(Timer_enum timer)=0;
};
#endif