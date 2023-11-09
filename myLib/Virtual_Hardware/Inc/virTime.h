/**
*********************************************************************
*********
* @project_name :car0
* @file : virTime.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/9 
*********************************************************************
*********
*/
//

#ifndef CAR0_VIRTIME_H
#define CAR0_VIRTIME_H
#include "Resources.h"

class virTime {
public:
    virtual void timer_init(Timer_enum timer, uint32_t period)=0;
    virtual void timer_start(Timer_enum timer)=0;
    virtual void timer_stop(Timer_enum timer)=0;
    virtual void timer_reset(Timer_enum timer)=0;
    virtual bool timer_is_running(Timer_enum timer)=0;

    virtual void timer_set_callback(Timer_enum timer, void (*callback)())=0;
    virtual void timer_clear_callback(Timer_enum timer)=0;

    // PWM related functions
    virtual void pwm_init(Timer_enum timer, uint32_t frequency, float duty_cycle)=0;
    virtual void pwm_start(Timer_enum timer)=0;
    virtual void pwm_stop(Timer_enum timer)=0;
    virtual void pwm_set_duty_cycle(Timer_enum timer, float duty_cycle)=0;
};


#endif //CAR0_VIRTIME_H
