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
public:

    void timerGreatPsc(Timer_enum timer, uint32_t arr) override;

    void timerStartOnce(Timer_enum timer) override;

    void timerStartPeriodic(Timer_enum timer) override;

    void timerStop(Timer_enum timer) override;

    void timerDelete(Timer_enum timer) override;

protected:

};



#endif //CAR0_MYBASETIME_H
