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
    this->m_genericMode=genericMode;
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
    virTime->timer_reset(time_x);
    return 1;
}

uint32_t BaseTime::TimeGetCurrentValue() {
    virTime->timer_getCurrentValue(time_x);
    return 1;
}

uint32_t BaseTime::TimeGetRemainingTime() {
    virTime->timer_getRemainingTime(time_x);
    return 1;
}

void BaseTime::TimeSetCallBack(CallBack callBack) {
    virTime->timer_set_callback(time_x,callBack);
}

void BaseTime::TimeClearCallBack() {
    virTime->timer_clear_callback(time_x);
}

uint32_t BaseTime::TimePWM_getFrequency() const {
    return virTime->pwm_getFrequency(time_x);
}

float BaseTime::TimePWM_getDutyCycle() const {
    return virTime->pwm_getDutyCycle(time_x, m_genericMode);
}

void BaseTime::TimePWM_setPhase(float phase) {
    virTime->pwm_setPhase(time_x,phase,m_genericMode);
}

void BaseTime::TimePWM_setPulseWidth(uint32_t pulse_width) {
    virTime->pwm_setPulseWidth(time_x,pulse_width,m_genericMode);
}

void BaseTime::TimePWM_start() {
    virTime->pwm_start(time_x,m_genericMode);
}

void BaseTime::TimePWM_stop() {
    virTime->pwm_stop(time_x,m_genericMode);

}

void BaseTime::TimePWM_set_duty_cycle(uint16_t duty_cycle) {
    virTime->pwm_set_duty_cycle(time_x,duty_cycle,m_genericMode);
}

uint32_t BaseTime::TimeGetCurrentFrequency() {
    //计算方式都一致直接使用PWM的函数进行计算
    return virTime->pwm_getFrequency(time_x);
}

uint32_t BaseTime::TimeCaputerHigihLevel() {
    return virTime->CaptureHighLevelTime();
}





