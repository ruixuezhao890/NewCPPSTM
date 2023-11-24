/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseOutputCountTimer.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/24 
*********************************************************************
*********
*/
//

#include "Base_Hardware/BaseTime/Inc/BaseOutputCountTimer.h"
BaseOutputCountTimer::BaseOutputCountTimer() {

}

BaseOutputCountTimer::BaseOutputCountTimer(Timer_enum timerEnum, uint8_t PreemptPriority, uint8_t SubPriority)
:_timer(timerEnum),PreemptPriority(PreemptPriority),SubPriority(SubPriority){

}

BaseOutputCountTimer::BaseOutputCountTimer(Timer_enum timerEnum, Pin_enum pin, uint8_t AFMode, uint8_t PreemptPriority,
                                           uint8_t SubPriority): BaseOutputCountTimer(timerEnum,PreemptPriority,SubPriority) {
    AdvancedTimer::UniversalAFIO.gpio_init(pin,GpioMode::af_pp,GpioPull::pullup,AFMode);
}

BaseOutputCountTimer::~BaseOutputCountTimer() {

}

template<typename TArg>
void
BaseOutputCountTimer::startOutputCount(uint32_t arr, uint32_t psc, uint8_t TIMExOutputCount_Channel, void (*callback)(TArg),
                                       TArg arg) {
    ExitValue.TimeCaptureExit[_timer]=reinterpret_cast<callback_with_arg_t>(callback);
    ExitValue.arg[_timer]=reinterpret_cast<void*>(arg);
    this->m_arr=arr;this->m_psc=psc,m_TIMExOutputCount_Channel=TIMExOutputCount_Channel;
    ConfigOutputCount();
    AdvancedTimer::startOutputPWMNum(_timer,m_TIMExOutputCount_Channel);
}

void BaseOutputCountTimer::stopOutputCount() {
    AdvancedTimer::stopOutputPWMNum(_timer,m_TIMExOutputCount_Channel);
}

void BaseOutputCountTimer::deletOutputCount() {
    AdvancedTimer::deleteOutputPWMNum(_timer);
}

void BaseOutputCountTimer::ConfigOutputCount() {
    AdvancedTimer::setOutputPWMNumGreat(_timer,m_psc,m_arr,m_TIMExOutputCount_Channel,PreemptPriority,SubPriority);
}

void BaseOutputCountTimer::setOutputOutputCountNum(uint32_t PNum) {
   AdvancedTimer::setOutputPWMNum(_timer,PNum);
}
