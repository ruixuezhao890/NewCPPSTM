/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseDeadZoneTimer.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/25 
*********************************************************************
*********
*/
//

#include "Base_Hardware/BaseTime/Inc/BaseDeadZoneTimer.h"

BaseDeadZoneTimer::BaseDeadZoneTimer() {

}

BaseDeadZoneTimer::BaseDeadZoneTimer(Timer_enum timerEnum, uint8_t PreemptPriority, uint8_t SubPriority) {
_timer=timerEnum;
this->PreemptPriority=PreemptPriority;
this->SubPriority=SubPriority;
}

BaseDeadZoneTimer::BaseDeadZoneTimer(Timer_enum timerEnum, Pin_enum pin, uint8_t AFMode, uint8_t PreemptPriority,
                                     uint8_t SubPriority)
 : BaseDeadZoneTimer(timerEnum,PreemptPriority,SubPriority)                                    {
    AdvancedTimer::deadZoneMultiplexPin(pin,AFMode);
}

BaseDeadZoneTimer::BaseDeadZoneTimer(Timer_enum timerEnum, std::vector<Pin_enum> pin, uint8_t AFMode,
                                     uint8_t PreemptPriority, uint8_t SubPriority)
 : BaseDeadZoneTimer(timerEnum,PreemptPriority,SubPriority)                                    {
    for (int i = 0; i < pin.size(); ++i) {
        AdvancedTimer::deadZoneMultiplexPin(pin[i],AFMode);
    }
}

BaseDeadZoneTimer::~BaseDeadZoneTimer() {

}

void BaseDeadZoneTimer::startDeadZoneTimer(uint32_t arr, uint32_t psc, std::vector<uint8_t> TIMExCapture_Channel) {
    m_arr=arr;m_psc=psc;
    ConfigDeadZoneTimer();
    for (unsigned char i : TIMExCapture_Channel) {
        AdvancedTimer::startdeadZone(_timer, i);
    }

}

void BaseDeadZoneTimer::stopDeadZoneTimer() {
   AdvancedTimer::startdeadZone(_timer,m_TIMExDeadZoneTimer_Channel);
}

void BaseDeadZoneTimer::deletDeadZoneTimer() {
    AdvancedTimer::stopdeadZone(_timer,m_TIMExDeadZoneTimer_Channel);
}

void BaseDeadZoneTimer::setPWMDeadZoneTimer(uint16_t ccr, uint8_t dtg) {
    AdvancedTimer::setPWMdeadZone(_timer,ccr,dtg);
}

void BaseDeadZoneTimer::ConfigDeadZoneTimer() {
    deadZoneGreat(_timer,m_psc,m_arr,PreemptPriority,SubPriority);
}
