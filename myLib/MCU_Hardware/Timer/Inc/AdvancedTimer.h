/**
*********************************************************************
*********
* @project_name :car0
* @file : AdvancedTimer.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/23 
*********************************************************************
*********
*/
//

#ifndef CAR0_ADVANCEDTIMER_H
#define CAR0_ADVANCEDTIMER_H
#include "MyUniversalTimer.h"
#include "MyGPIO.h"

class AdvancedTimer :public MyUniversalTimer{
protected:
    void setOutputPWMNumGreat(Timer_enum timer, uint32_t psc, uint32_t arr, uint8_t TIMExPWM_Channel,
                              uint8_t PreemptPriority, uint8_t SubPriority);

    void startOutputPWMNum(Timer_enum timer,uint8_t TIMExPWM_Channel);
    void stopOutputPWMNum(Timer_enum timer,uint8_t TIMExPWM_Channel);
    void deleteOutputPWMNum(Timer_enum timer);
    void setOutputPWMNum(Timer_enum timer, uint32_t NumPWM);

    uint32_t m_arr;
    MyGPIO UniversalAFIO;
};


#endif //CAR0_ADVANCEDTIMER_H
