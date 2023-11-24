/**
*********************************************************************
*********
* @project_name :car0
* @file : BasePulseCounterTimer.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/23 
*********************************************************************
*********
*/
//

#include "Base_Hardware/BaseTime/Inc/BasePulseCounterTimer.h"
BasePulseCounterTimer::BasePulseCounterTimer() {

}

BasePulseCounterTimer::BasePulseCounterTimer(Timer_enum timerEnum, uint8_t PreemptPriority, uint8_t SubPriority):
_timer(timerEnum),PreemptPriority(PreemptPriority),SubPriority(SubPriority){

}

BasePulseCounterTimer::BasePulseCounterTimer(Timer_enum timerEnum, Pin_enum pin, uint8_t AFMode,
                                             uint8_t PreemptPriority, uint8_t SubPriority)
: BasePulseCounterTimer(timerEnum,PreemptPriority,SubPriority){
    MyUniversalTimer::timerPulseCounterMultiplexPin(pin,AFMode);
}

BasePulseCounterTimer::~BasePulseCounterTimer() {
    this->deletePulseCounter();
}

template<typename TArg>
void BasePulseCounterTimer::startPulseCounter(uint32_t psc, uint8_t TIMExPulseCounter_Channel, void (*callback)(TArg),
                                              TArg arg) {
    m_psc=psc;m_arr=65535;m_TIMExPulseCounter_Channel=TIMExPulseCounter_Channel;
    ExitValue.TimeCaptureExit[_timer]=reinterpret_cast<callback_with_arg_t>(callback);
    ExitValue.arg[_timer]=reinterpret_cast<void*>(arg);
   ConfigPulseCounter();


}

void BasePulseCounterTimer::stopPulseCounter() {
    timerPulseCounterStop(_timer,m_TIMExPulseCounter_Channel);
}

void BasePulseCounterTimer::deletePulseCounter() {
    timerPulseCounterDelete(_timer,m_TIMExPulseCounter_Channel);
}

uint32_t BasePulseCounterTimer::getPulseCounterCount() {
    return timerPulseCounterCount(_timer);
}

void BasePulseCounterTimer::ConfigPulseCounter() {
    timerPulseCounterGreat(_timer,m_psc,m_arr,PreemptPriority,SubPriority);
    timerPulseCounterStart(_timer,m_TIMExPulseCounter_Channel);
}

void BasePulseCounterTimer::restartPulseCounter() {
    timerPulseCounterRestart(_timer);
}
