/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseOutputCountTimer.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/24 
*********************************************************************
*********
*/
//

#ifndef CAR0_BASEOUTPUTCOUNTTIMER_H
#define CAR0_BASEOUTPUTCOUNTTIMER_H
#include "AdvancedTimer.h"
#include  "timeIT.h"
class BaseOutputCountTimer: public AdvancedTimer{
public:
    BaseOutputCountTimer();
    BaseOutputCountTimer(Timer_enum timerEnum, uint8_t PreemptPriority , uint8_t SubPriority);
    BaseOutputCountTimer(Timer_enum timerEnum, Pin_enum pin, uint8_t AFMode, uint8_t PreemptPriority = 1,
            uint8_t SubPriority = 3);
    // 析构函数
    ~BaseOutputCountTimer();

    template<typename TArg>
    void startOutputCount(uint32_t arr, uint32_t psc, uint8_t TIMExOutputCount_Channel,
                      void (*callback)(TArg)=OutputCounterNUm, TArg arg=0);

    // 停止OutputCount
    void stopOutputCount();

    void deletOutputCount();

    void  setOutputOutputCountNum(uint32_t PNum);
protected:
    void ConfigOutputCount();
private:
    // 定时器的句柄
    Timer_enum _timer=Timer_enum::TIMER_END;
    uint32_t m_psc;
    uint32_t m_arr;
    uint8_t m_TIMExOutputCount_Channel;
    uint8_t PreemptPriority;
    uint8_t SubPriority;

};




#endif //CAR0_BASEOUTPUTCOUNTTIMER_H
