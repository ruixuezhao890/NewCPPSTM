/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseCaptureTimer.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/22 
*********************************************************************
*********
*/
//

#include "Base_Hardware/BaseTime/Inc/BaseCaptureTimer.h"


BaseCaptureTimer::BaseCaptureTimer() {

}

BaseCaptureTimer::BaseCaptureTimer(Timer_enum timerEnum, uint8_t PreemptPriority, uint8_t SubPriority)
:_timer(timerEnum), PreemptPriority(PreemptPriority),SubPriority(SubPriority)
{

}

BaseCaptureTimer::BaseCaptureTimer(Timer_enum timerEnum, Pin_enum pin, uint8_t AFMode, uint8_t PreemptPriority,
                                   uint8_t SubPriority): BaseCaptureTimer(timerEnum, PreemptPriority, SubPriority) {

    MyUniversalTimer::timerCaptureMultiplexPin(pin, AFMode);

}

BaseCaptureTimer::~BaseCaptureTimer() {
    deletCapture();
}
template<typename TArg>
void BaseCaptureTimer::startCapture(uint32_t arr, uint32_t psc, uint8_t TIMExCapture_Channel,
                                    void (*callback)(TArg), TArg arg) {
    if (_timer==TIMER_END){
        return;
    }
    m_psc=psc;m_arr=arr;m_TIMExCapture_Channel=TIMExCapture_Channel;
    ExitValue.TimeCaptureExit[_timer]=reinterpret_cast<callback_with_arg_t>(callback);
    ExitValue.arg[_timer]=reinterpret_cast<void*>(arg);
    ConfigCapture();
}

void BaseCaptureTimer::stopCapture() {
    MyUniversalTimer::stopCapture(_timer,m_TIMExCapture_Channel);
}

uint32_t BaseCaptureTimer::getCaptureHighLevel() {
    return MyUniversalTimer::getCaptureHighLevel();
}

void BaseCaptureTimer::ConfigCapture() {
    MyUniversalTimer::timerCaptureGreat(_timer,m_psc,m_arr,PreemptPriority,SubPriority);
    MyUniversalTimer::startCapturePeriodic(_timer,m_TIMExCapture_Channel);
}

void BaseCaptureTimer::deletCapture() {
    MyUniversalTimer::deleteCaptureTimer(_timer,m_TIMExCapture_Channel);
}
