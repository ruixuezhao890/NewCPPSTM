/**
*********************************************************************
*********
* @project_name :car0
* @file : MyBaseTime.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/10
*********************************************************************
*********
*/
//

#ifndef CAR0_MYBASETIME_H
#define CAR0_MYBASETIME_H
#define MAXTIMNUM 14
#include "virTime.h"

class MyBaseTime: public virTime{
protected:

    uint32_t timerGreatPsc(Timer_enum timer, uint32_t arr,
                           uint8_t PreemptPriority, uint8_t SubPriority) override;
    TIM_HandleTypeDef *
    timerGreatPsc(Timer_enum timer, uint32_t psc, uint32_t arr, uint8_t PreemptPriority, uint8_t SubPriority) override;

protected:

    void timerStartOnce(Timer_enum timer) override;

    void timerStartPeriodic(Timer_enum timer) override;

    void timerStop(Timer_enum timer) override;

    void timerDelete(Timer_enum timer) override;



};



#endif //CAR0_MYBASETIME_H
