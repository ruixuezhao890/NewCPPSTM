/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseUniversalTimer.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/21 
*********************************************************************
*********
*/
//

#ifndef CAR0_BASEUNIVERSALTIMER_H
#define CAR0_BASEUNIVERSALTIMER_H
#include "MyUniversalTimer.h"

class BaseUniversalTimer: public MyUniversalTimer{
public:
    // 构造函数
    BaseUniversalTimer();
    BaseUniversalTimer(Timer_enum timerEnum, uint8_t PreemptPriority=3, uint8_t SubPriority=3);
    // 析构函数
    ~BaseUniversalTimer();
    // 启动PWM
    void startPWM();

    // 停止PWM
    void stopPWM();


protected:
    // 定时器的句柄
    Timer_enum _timer=Timer_enum::TIMER_END;
    uint8_t m_TIMExPWM_Channel;
    uint8_t PreemptPriority;
    uint8_t SubPriority;
};


#endif //CAR0_BASEUNIVERSALTIMER_H
