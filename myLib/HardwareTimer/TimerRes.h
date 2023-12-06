/**
*********************************************************************
*********
* @project_name :car0
* @file : TimerRes.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/12/6 
*********************************************************************
*********
*/
//

#ifndef CAR0_TIMERRES_H
#define CAR0_TIMERRES_H
#define   MAXTIMNUM 14
#define HAVE_TIMER1
//#define HAVE_TIMER2
//#define HAVE_TIMER3
//#define HAVE_TIMER4
//#define HAVE_TIMER5
#define HAVE_TIMER6
//#define HAVE_TIMER7
//#define HAVE_TIMER8
//#define HAVE_TIMER9
//#define HAVE_TIMER10
//#define HAVE_TIMER11
//#define HAVE_TIMER12
//#define HAVE_TIMER13
//#define HAVE_TIMER14

HardwareTimer * getTimerOOP(TIM_HandleTypeDef *instance){
#ifdef HAVE_TIMER1
    if (instance->Instance==TIM1){
        return &TIMER1;
    }
#endif
#ifdef HAVE_TIMER2
    if (instance->Instance==TIM2){
        return &TIMER2;
    }
#endif
#ifdef HAVE_TIMER3
    if (instance->Instance==TIM3){
        return &TIMER3;
    }
#endif
#ifdef HAVE_TIMER4
    if (instance->Instance==TIM4){
        return &TIMER4;
    }
#endif
#ifdef HAVE_TIMER5
    if (instance->Instance==TIM5){
        return &TIMER5;
    }
#endif
#ifdef HAVE_TIMER6
    if (instance->Instance==TIM6){
        return &TIMER6;
    }
#endif
#ifdef HAVE_TIMER7
    if (instance->Instance==TIM7){
        return &TIMER7;
    }
#endif
#ifdef HAVE_TIMER8
    if (instance->Instance==TIM8){
        return &TIMER8;
    }
#endif
#ifdef HAVE_TIMER9
    if (instance->Instance==TIM9){
        return &TIMER9;
    }
#endif
#ifdef HAVE_TIMER10
    if (instance->Instance==TIM10){
        return &TIMER10;
    }
#endif
#ifdef HAVE_TIMER11
    if (instance->Instance==TIM11){
        return &TIMER11;
    }
#endif
#ifdef HAVE_TIMER12
    if (instance->Instance==TIM12){
        return &TIMER12;
    }
#endif
#ifdef HAVE_TIMER13
    if (instance->Instance==TIM13){
        return &TIMER13;
    }
#endif
#ifdef HAVE_TIMER14
    if (instance->Instance==TIM14){
        return &TIMER14;
    }
#endif
    return nullptr;
}
#endif //CAR0_TIMERRES_H
