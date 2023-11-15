/**
*********************************************************************
*********
* @project_name :car0
* @file : MyTime.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/10
*********************************************************************
*********
*/
//

#ifndef CAR0_MYTIME_H
#define CAR0_MYTIME_H
#define MAXTIMNUM 14
#include "virTime.h"

class MyTime:public virTime{
public:
    void timer_BasicTimerInit(Timer_enum timer, uint32_t arr, uint32_t psc) override;

    void timer_GenericTimerInit(Timer_enum timer, uint32_t arr, uint32_t psc, GenericTIMMode genericMode) override;

    void timer_AdvancedTimerInit(Timer_enum timer, uint32_t arr, uint32_t psc, AdvancedTIMMode advancedMode) override;

    void timer_start(Timer_enum timer) override;

    void timer_stop(Timer_enum timer) override;

    void timer_reset(Timer_enum timer) override;

    bool timer_is_running(Timer_enum timer) override;

    uint32_t timer_getCurrentValue(Timer_enum timer) override;

    uint32_t timer_getPeriod(Timer_enum timer) override;

    uint32_t timer_getRemainingTime(Timer_enum timer) override;

    void timer_set_callback(Timer_enum timer, void (*callback)()) override;

    void timer_clear_callback(Timer_enum timer) override;

    uint32_t pwm_getFrequency(Timer_enum timer, GenericTIMMode genericMode) const override;

    float pwm_getDutyCycle(Timer_enum timer, uint16_t setData, GenericTIMMode genericMode) const override;

    void pwm_setPhase(Timer_enum timer, float phase, GenericTIMMode genericMode) override;

    void pwm_setPulseWidth(Timer_enum timer, uint32_t pulse_width, GenericTIMMode genericMode) override;

    void pwm_start(Timer_enum timer, GenericTIMMode genericMode) override;

    void pwm_stop(Timer_enum timer, GenericTIMMode genericMode) override;

    void pwm_set_duty_cycle(Timer_enum timer, uint16_t duty_cycle, GenericTIMMode genericMode) override;

    void pwm_setInterruptCallback(Timer_enum timer, void (*callback)(void), GenericTIMMode genericMode) override;

protected:
    void OpenRccTime(Timer_enum timer);
    uint8_t getTIMEx_IRQn(Timer_enum timer);
    uint32_t getTimeInstance(Timer_enum timer);
    void timer_PWMCHYInit(Timer_enum timer, uint32_t arr, uint32_t psc, GenericTIMMode genericMode);
//    void InitAllTime(Timer_enum timer);

};
extern "C"{
void TIM1_BRK_TIM9_IRQHandler(void);
void TIM1_UP_TIM10_IRQHandler(void);
void TIM1_TRG_COM_TIM11_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM5_IRQHandler(void);
void TIM6_DAC_IRQHandler(void);
void TIM7_IRQHandler(void);
void TIM8_BRK_TIM12_IRQHandler(void);
void TIM8_UP_TIM13_IRQHandler(void);
void TIM8_TRG_COM_TIM14_IRQHandler();
}

#endif //CAR0_MYTIME_H
