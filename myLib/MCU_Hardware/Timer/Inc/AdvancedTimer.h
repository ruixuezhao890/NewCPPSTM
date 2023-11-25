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
    /*输出指定数目的PWM波形相关代码*/
    void setOutputPWMNumGreat(Timer_enum timer, uint32_t psc, uint32_t arr, uint8_t TIMExPWM_Channel,
                              uint8_t PreemptPriority, uint8_t SubPriority);

    void startOutputPWMNum(Timer_enum timer,uint8_t TIMExPWM_Channel);
    void stopOutputPWMNum(Timer_enum timer,uint8_t TIMExPWM_Channel);
    void deleteOutputPWMNum(Timer_enum timer);
    void setOutputPWMNum(Timer_enum timer, uint32_t NumPWM);

    /*输出比较相关代码*/
    void
    setOutputCompareGreat(Timer_enum timer, uint32_t psc, uint32_t arr, uint8_t PreemptPriority, uint8_t SubPriority);
    void timerOutputCompareMultiplexPin(Pin_enum pin, uint8_t Alternate);
    void startOutputCompare(Timer_enum timer, uint16_t PluseNum, uint8_t TIMExPWM_Channel);
    void stopOutputCompare(Timer_enum timer,uint8_t TIMExPWM_Channel);
    void deleteOutputCompare(Timer_enum timer);


    /*互补输出带死区控制相关代码*/
    void deadZoneGreat(Timer_enum timer, uint32_t psc, uint32_t arr, uint8_t PreemptPriority, uint8_t SubPriority);
    void deadZoneMultiplexPin(Pin_enum pin, uint8_t Alternate);
    void startdeadZone(Timer_enum timer, uint8_t TIMExPWM_Channel);
    void stopdeadZone(Timer_enum timer,uint8_t TIMExPWM_Channel);
    void deletedeadZone(Timer_enum timer);
    void setPWMdeadZone(Timer_enum timer,uint16_t ccr, uint8_t dtg);
protected:
    uint32_t m_arr;
    MyGPIO UniversalAFIO;
    TIM_BreakDeadTimeConfigTypeDef g_sbreak_dead_time_config = {0};
};


#endif //CAR0_ADVANCEDTIMER_H
