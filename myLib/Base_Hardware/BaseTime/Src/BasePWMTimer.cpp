/**
*********************************************************************
*********
* @project_name :car0
* @file : BasePWMTimer.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/21 
*********************************************************************
*********
*/
//

#include "Base_Hardware/BaseTime/Inc/BasePWMTimer.h"

BasePWMTimer::BasePWMTimer() {

}
BasePWMTimer::BasePWMTimer(Timer_enum timerEnum, uint8_t PreemptPriority, uint8_t SubPriority):
_timer(timerEnum),PreemptPriority(PreemptPriority),SubPriority(SubPriority) {

}
BasePWMTimer::BasePWMTimer(Timer_enum timerEnum, Pin_enum pin, uint8_t AFMode, uint8_t PreemptPriority,
                           uint8_t SubPriority)
: BasePWMTimer(timerEnum,PreemptPriority, SubPriority)
{
    MyUniversalTimer::timerPWMMultiplexPin(pin,AFMode);
}

BasePWMTimer::~BasePWMTimer() {

}

void BasePWMTimer::startPWM_ms(uint32_t arr, uint32_t psc, uint8_t TIMExPWM_Channel, float DutyCycle) {
    m_arr=arr;m_psc=psc;
    m_TIMExPWM_Channel=TIMExPWM_Channel;
    ConfigPWM(DutyCycle);
}

void BasePWMTimer::stopPWM() {
    MyUniversalTimer::stopPWM(_timer,m_TIMExPWM_Channel);
}



void BasePWMTimer::ConfigPWM(float DutyCycle) {
    MyUniversalTimer::timerGreatPsc(_timer,m_psc,m_arr,PreemptPriority,SubPriority);
    MyUniversalTimer::timerPWMGreat(_timer,m_TIMExPWM_Channel,DutyCycle);
    startPWMPeriodic(_timer,m_TIMExPWM_Channel);
}

void BasePWMTimer::setPWMDutyCycle(uint32_t DutyCycle) {
    MyUniversalTimer::setPWMDutyCycle(DutyCycle,_timer,m_TIMExPWM_Channel);
}

void BasePWMTimer::deletePWM() {
    MyUniversalTimer::deletePWMTimer(_timer);
}




