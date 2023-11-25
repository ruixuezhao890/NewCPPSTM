/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseDeadZoneTimer.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/25 
*********************************************************************
*********
*/
//

#ifndef CAR0_BASEDEADZONETIMER_H
#define CAR0_BASEDEADZONETIMER_H
#include "AdvancedTimer.h"
#include "vector"
class BaseDeadZoneTimer: public AdvancedTimer{
public:
    BaseDeadZoneTimer();
    BaseDeadZoneTimer(Timer_enum timerEnum, uint8_t PreemptPriority , uint8_t SubPriority);
    BaseDeadZoneTimer(Timer_enum timerEnum, Pin_enum pin, uint8_t AFMode, uint8_t PreemptPriority,
            uint8_t SubPriority);
    BaseDeadZoneTimer(Timer_enum timerEnum, std::vector<Pin_enum>pin, uint8_t AFMode, uint8_t PreemptPriority = 3,
            uint8_t SubPriority = 3);
    // 析构函数
    ~BaseDeadZoneTimer();
    // 启动Capture

    void startDeadZoneTimer(uint32_t arr, uint32_t psc, std::vector<uint8_t> TIMExCapture_Channel);

    // 停止Capture
    void stopDeadZoneTimer();

    void deletDeadZoneTimer();

    void setPWMDeadZoneTimer(uint16_t ccr, uint8_t dtg);
protected:
    void ConfigDeadZoneTimer();
private:
    // 定时器的句柄
    Timer_enum _timer=Timer_enum::TIMER_END;
    uint32_t m_psc;
    uint32_t m_arr;
    uint8_t m_TIMExDeadZoneTimer_Channel;
    uint8_t PreemptPriority;
    uint8_t SubPriority;
};


#endif //CAR0_BASEDEADZONETIMER_H
