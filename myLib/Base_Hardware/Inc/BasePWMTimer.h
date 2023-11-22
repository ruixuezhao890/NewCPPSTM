/**
*********************************************************************
*********
* @project_name :car0
* @file : BasePWMTimer.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/21 
*********************************************************************
*********
*/
//

#ifndef CAR0_BASEPWMTIMER_H
#define CAR0_BASEPWMTIMER_H
#include "MyUniversalTimer.h"
#include "MyGPIO.h"
class BasePWMTimer: public MyUniversalTimer{
public:
    // 构造函数
    BasePWMTimer();
    BasePWMTimer(Timer_enum timerEnum, uint8_t PreemptPriority = 3, uint8_t SubPriority = 3);
    BasePWMTimer(Timer_enum timerEnum, Pin_enum pin, uint8_t AFMode, uint8_t PreemptPriority = 3,
                 uint8_t SubPriority = 3);
    // 析构函数
    ~BasePWMTimer();
    // 启动PWM

    void startPWM_ms(uint32_t arr, uint32_t psc, uint8_t TIMExPWM_Channel, float DutyCycle);

    // 停止PWM
    void stopPWM();

    void setPWMDutyCycle(uint32_t DutyCycle);
protected:
    void ConfigPWM( float DutyCycle);
private:
    // 定时器的句柄
    Timer_enum _timer=Timer_enum::TIMER_END;
    uint32_t m_psc;
    uint32_t m_arr;
    uint8_t m_TIMExPWM_Channel;
    uint8_t PreemptPriority;
    uint8_t SubPriority;
};


#endif //CAR0_BASEPWMTIMER_H
