/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseCaptureTimer.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/22 
*********************************************************************
*********
*/
//

#ifndef CAR0_BASECAPTURETIMER_H
#define CAR0_BASECAPTURETIMER_H
#include "MyUniversalTimer.h"

class BaseCaptureTimer: public MyUniversalTimer{
public:
    BaseCaptureTimer();
    BaseCaptureTimer(Timer_enum timerEnum, uint8_t PreemptPriority = 3, uint8_t SubPriority = 3);
    BaseCaptureTimer(Timer_enum timerEnum, Pin_enum pin, uint8_t AFMode, uint8_t PreemptPriority = 3,
            uint8_t SubPriority = 3);
    // 析构函数
    ~BaseCaptureTimer();
    // 启动Capture
    template<typename TArg>
    void startCapture(uint32_t arr, uint32_t psc, uint8_t TIMExCapture_Channel,
                         void (*callback)(TArg), TArg arg );

    // 停止Capture
    void stopCapture();

    void getCaptureHighLevel();
protected:
    void ConfigCapture( float DutyCycle);
private:
    // 定时器的句柄
    Timer_enum _timer=Timer_enum::TIMER_END;
    uint32_t m_psc;
    uint32_t m_arr;
    uint8_t m_TIMExCapture_Channel;
    uint8_t PreemptPriority;
    uint8_t SubPriority;

};


#endif //CAR0_BASECAPTURETIMER_H
