/**
*********************************************************************
*********
* @project_name :car0
* @file : BasePulseCounterTimer.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/23 
*********************************************************************
*********
*/
//

#ifndef CAR0_BASEPULSECOUNTERTIMER_H
#define CAR0_BASEPULSECOUNTERTIMER_H
#include "MyUniversalTimer.h"
#include "timeIT.h"
class BasePulseCounterTimer: public MyUniversalTimer{
public:
    BasePulseCounterTimer();
    BasePulseCounterTimer(Timer_enum timerEnum, uint8_t PreemptPriority , uint8_t SubPriority);
    BasePulseCounterTimer(Timer_enum timerEnum, Pin_enum pin, uint8_t AFMode, uint8_t PreemptPriority = 1,
            uint8_t SubPriority = 3);
    // 析构函数
    ~BasePulseCounterTimer();
    // 启动PulseCounter
    template<typename TArg>
    void startPulseCounter(uint32_t psc, uint8_t TIMExPulseCounter_Channel, void (*callback)(TArg) = CounterPulseNum,
                           TArg arg = 0);

    // 停止PulseCounter
    void stopPulseCounter();

    void restartPulseCounter();

    void deletePulseCounter();

    uint32_t getPulseCounterCount();
protected:
    void ConfigPulseCounter();
private:
    // 定时器的句柄
    Timer_enum _timer=Timer_enum::TIMER_END;
    uint32_t m_psc;
    uint32_t m_arr;
    uint8_t m_TIMExPulseCounter_Channel;
    uint8_t PreemptPriority;
    uint8_t SubPriority;
};




#endif //CAR0_BASEPULSECOUNTERTIMER_H
