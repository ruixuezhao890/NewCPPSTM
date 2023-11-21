/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseUniversalTimer.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/21 
*********************************************************************
*********
*/
//

#include "BaseUniversalTimer.h"

BaseUniversalTimer::BaseUniversalTimer() {

}

BaseUniversalTimer::BaseUniversalTimer(Timer_enum timerEnum, uint8_t PreemptPriority, uint8_t SubPriority){

}

BaseUniversalTimer::~BaseUniversalTimer() {

}

void BaseUniversalTimer::startPWM() {

    startPWMPeriodic(_timer,m_TIMExPWM_Channel);
}

void BaseUniversalTimer::stopPWM() {
    MyUniversalTimer::stopPWM(_timer,m_TIMExPWM_Channel);
}
