/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseCompareOutTimer.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/24 
*********************************************************************
*********
*/
//

#ifndef CAR0_BASECOMPAREOUTTIMER_H
#define CAR0_BASECOMPAREOUTTIMER_H
#include "AdvancedTimer.h"
#include "vector"
class BaseCompareOutTimer: public AdvancedTimer{
public:
    BaseCompareOutTimer();
    BaseCompareOutTimer(Timer_enum timerEnum, uint8_t PreemptPriority , uint8_t SubPriority);
    BaseCompareOutTimer(Timer_enum timerEnum, Pin_enum pin, uint8_t AFMode, uint8_t PreemptPriority,
                                             uint8_t SubPriority);
    BaseCompareOutTimer(Timer_enum timerEnum, std::vector<Pin_enum>pin, uint8_t AFMode, uint8_t PreemptPriority = 3,
            uint8_t SubPriority = 3);
    // 析构函数
    ~BaseCompareOutTimer();
    // 启动Capture

    void startCompareOut(uint32_t arr, uint32_t psc, std::vector<uint16_t> &PulseNum,
                         std::vector<uint8_t> &TIMExCapture_Channel);

    // 停止Capture
    void stopCompareOut();

    void deletCompareOut();


protected:
    void ConfigCompareOut();
private:
    // 定时器的句柄
    Timer_enum _timer=Timer_enum::TIMER_END;
    uint32_t m_psc;
    uint32_t m_arr;
    std::vector<uint8_t> m_TIMExCompareOut_Channel;
    uint8_t PreemptPriority;
    uint8_t SubPriority;
};



#endif //CAR0_BASECOMPAREOUTTIMER_H
