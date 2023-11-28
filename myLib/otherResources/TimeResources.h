/**
*********************************************************************
*********
* @project_name :car0
* @file : TimeResources.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/27 
*********************************************************************
*********
*/
//

#ifndef CAR0_TIMERESOURCES_H
#define CAR0_TIMERESOURCES_H
#include "stm32f4xx.h"
#define HAVE_TIMER1
#define HAVE_TIMER2
#define HAVE_TIMER3
#define HAVE_TIMER4
#define HAVE_TIMER5
#define HAVE_TIMER6
#define HAVE_TIMER7
#define HAVE_TIMER8
#define HAVE_TIMER9
#define HAVE_TIMER10
#define HAVE_TIMER11
#define HAVE_TIMER12
#define HAVE_TIMER13
#define HAVE_TIMER14
typedef enum
{
#ifdef HAVE_TIMER1
    TIMER_1,
#endif
#ifdef HAVE_TIMER2
    TIMER_2,
#endif
#ifdef HAVE_TIMER3
    TIMER_3,
#endif
#ifdef HAVE_TIMER4
    TIMER_4,
#endif
#ifdef HAVE_TIMER5
    TIMER_5,
#endif
#ifdef HAVE_TIMER6
    TIMER_6,
#endif
#ifdef HAVE_TIMER7
    TIMER_7,
#endif
#ifdef HAVE_TIMER8
    TIMER_8,
#endif
#ifdef HAVE_TIMER9
    TIMER_9,
#endif
#ifdef HAVE_TIMER10
    TIMER_10,
#endif
#ifdef HAVE_TIMER11
    TIMER_11,
#endif
#ifdef HAVE_TIMER12
    TIMER_12,
#endif
#ifdef HAVE_TIMER13
    TIMER_13,
#endif
#ifdef HAVE_TIMER14
    TIMER_14,
#endif
    TIMER_END // 占位符，未使用
} Timer_enum;

enum class GenericMode{
    TIME_PWM,
    TIME_Capture,
    TIME_PulseCounting
};
enum class AdvancedMode{
    TIME_SpecifyPWM,
    TIME_Compare,
    TIME_DeadZoneControl,
    TIME_InputMode
};
#endif //CAR0_TIMERESOURCES_H
