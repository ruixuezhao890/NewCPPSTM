/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseTime.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/11 
*********************************************************************
*********
*/
//

#include "BaseTime.h"
virTime* virTime= nullptr;

BaseTime::BaseTime(Timer_enum timer) {
    this->time_x=timer;
    if (!virTime)virTime=new MyTime();
}

int BaseTime::beginBaseTime(uint32_t arr, uint32_t psc) {
    virTime->timer_BasicTimerInit(time_x,arr,psc);
    return 1;
}

int BaseTime::beginGenericTime(uint32_t arr, uint32_t psc,GenericTIMMode genericMode) {
    virTime->timer_GenericTimerInit(time_x,arr,psc,genericMode);
    return 1;
}

int BaseTime::beginAdvancedTime(uint32_t arr, uint32_t psc) {
    return 0;
}

int BaseTime::TimeStart() {
    virTime->timer_start(time_x);
    return 1;
}

int BaseTime::TimeStop() {
     virTime->timer_stop(time_x);
    return 1;
}

int BaseTime::TimeReset() {
    return 0;
}

uint32_t BaseTime::TimeGetCurrentValue() {
    return 0;
}

uint32_t BaseTime::TimeGetRemainingTime() {
    return 0;
}

void BaseTime::TimeSetCallBack(CallBack callBack) {
    virTime->timer_set_callback(time_x,callBack);
}

void BaseTime::TimeClearCallBack() {
    virTime->timer_clear_callback(time_x);
}

void BaseTime::TimePWMSetDutyCycle(uint16_t duty) {
    virTime->pwm_set_duty_cycle(time_x,duty,m_genericMode);
}
