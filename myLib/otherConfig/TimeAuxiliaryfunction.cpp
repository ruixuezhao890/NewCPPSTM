/**
*********************************************************************
*********
* @project_name :car0
* @file : TimeAuxiliaryfunction.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/20 
*********************************************************************
*********
*/
//
#include "TimeAuxiliaryfunction.h"
void     OpenRccTime(Timer_enum timer) {
    switch (timer)
    {
#ifdef HAVE_TIMER1
        case TIMER_1:
            // Your code for TIMER_1
            __HAL_RCC_TIM1_CLK_ENABLE();
            break;
#endif

#ifdef HAVE_TIMER2
        case TIMER_2:
            // Your code for TIMER_2
            __HAL_RCC_TIM2_CLK_ENABLE();
            break;
#endif

#ifdef HAVE_TIMER3
        case TIMER_3:
            // Your code for TIMER_3
            __HAL_RCC_TIM3_CLK_ENABLE();
            break;
#endif

#ifdef HAVE_TIMER4
        case TIMER_4:
            // Your code for TIMER_4
            __HAL_RCC_TIM4_CLK_ENABLE();
            break;
#endif

#ifdef HAVE_TIMER5
        case TIMER_5:
            // Your code for TIMER_5
            __HAL_RCC_TIM5_CLK_ENABLE();
            break;
#endif

#ifdef HAVE_TIMER6
        case TIMER_6:
            // Your code for TIMER_6
            __HAL_RCC_TIM6_CLK_ENABLE();
            break;
#endif

#ifdef HAVE_TIMER7
        case TIMER_7:
            __HAL_RCC_TIM7_CLK_ENABLE();
            // Your code for TIMER_7
            break;
#endif

#ifdef HAVE_TIMER8
        case TIMER_8:
            __HAL_RCC_TIM8_CLK_ENABLE();
            // Your code for TIMER_8
            break;
#endif

#ifdef HAVE_TIMER9
        case TIMER_9:
            __HAL_RCC_TIM9_CLK_ENABLE();
            // Your code for TIMER_9
            break;
#endif

#ifdef HAVE_TIMER10
        case TIMER_10:
            __HAL_RCC_TIM10_CLK_ENABLE();
            // Your code for TIMER_10
            break;
#endif

#ifdef HAVE_TIMER11
        case TIMER_11:
            __HAL_RCC_TIM11_CLK_ENABLE();
            // Your code for TIMER_11
            break;
#endif

#ifdef HAVE_TIMER12
        case TIMER_12:
            __HAL_RCC_TIM12_CLK_ENABLE();
            // Your code for TIMER_12
            break;
#endif

#ifdef HAVE_TIMER13
        case TIMER_13:
            __HAL_RCC_TIM13_CLK_ENABLE();
            // Your code for TIMER_13
            break;
#endif

#ifdef HAVE_TIMER14
        case TIMER_14:
            // Your code for TIMER_14
            __HAL_RCC_TIM14_CLK_ENABLE();
            break;
#endif

        case TIMER_END:
            // Placeholder for unused case
            break;
    }

}

uint8_t  getTIMEx_IRQn(Timer_enum timer) {
    switch (timer)
    {
#ifdef HAVE_TIMER1
        case TIMER_1:
            // Your code for TIMER_1
            return TIM1_BRK_TIM9_IRQn;

#endif

#ifdef HAVE_TIMER2
        case TIMER_2:
            // Your code for TIMER_2
            return TIM2_IRQn;

#endif

#ifdef HAVE_TIMER3
        case TIMER_3:
            // Your code for TIMER_3
            return TIM3_IRQn;
#endif

#ifdef HAVE_TIMER4
        case TIMER_4:
            // Your code for TIMER_4
            return TIM4_IRQn;
#endif

#ifdef HAVE_TIMER5
        case TIMER_5:
            // Your code for TIMER_5
            return TIM5_IRQn;
#endif

#ifdef HAVE_TIMER6
        case TIMER_6:
            return  TIM6_DAC_IRQn;
            // Your code for TIMER_6

#endif

#ifdef HAVE_TIMER7
        case TIMER_7:
            return TIM7_IRQn;
            // Your code for TIMER_7

#endif

#ifdef HAVE_TIMER8
        case TIMER_8:
            // Your code for TIMER_8
            return TIM8_BRK_TIM12_IRQn;
#endif

#ifdef HAVE_TIMER9
        case TIMER_9:
            // Your code for TIMER_9
            return TIM1_BRK_TIM9_IRQn;
#endif

#ifdef HAVE_TIMER10
        case TIMER_10:
            // Your code for TIMER_10
            return TIM1_UP_TIM10_IRQn;
#endif

#ifdef HAVE_TIMER11
        case TIMER_11:
            // Your code for TIMER_11
            return TIM1_TRG_COM_TIM11_IRQn;
#endif

#ifdef HAVE_TIMER12
        case TIMER_12:
            // Your code for TIMER_12
            return TIM8_BRK_TIM12_IRQn;
#endif

#ifdef HAVE_TIMER13
        case TIMER_13:
            // Your code for TIMER_13
            return TIM8_UP_TIM13_IRQn;
#endif

#ifdef HAVE_TIMER14
        case TIMER_14:
            // Your code for TIMER_14
            return TIM8_TRG_COM_TIM14_IRQn;
#endif

        case TIMER_END:
            // Placeholder for unused case
            break;
    }
    return 0;
}

uint32_t getTimeInstance(Timer_enum timer) {
    switch (timer)
    {
#ifdef HAVE_TIMER1
        case TIMER_1:
            // Your code for TIMER_1
            return (uint32_t)TIM1;
#endif

#ifdef HAVE_TIMER2
        case TIMER_2:
            // Your code for TIMER_2
            return (uint32_t)TIM2;
#endif

#ifdef HAVE_TIMER3
        case TIMER_3:
            // Your code for TIMER_3
            return (uint32_t)TIM3;
#endif

#ifdef HAVE_TIMER4
        case TIMER_4:
            // Your code for TIMER_4
            return (uint32_t)TIM4;
#endif

#ifdef HAVE_TIMER5
        case TIMER_5:
            // Your code for TIMER_5
            return (uint32_t)TIM5;
#endif

#ifdef HAVE_TIMER6
        case TIMER_6:
            // Your code for TIMER_6
            return (uint32_t)TIM6;
#endif

#ifdef HAVE_TIMER7
        case TIMER_7:
            // Your code for TIMER_7
            return (uint32_t)TIM7;
#endif

#ifdef HAVE_TIMER8
        case TIMER_8:
            // Your code for TIMER_8
            return (uint32_t)TIM8;
#endif

#ifdef HAVE_TIMER9
        case TIMER_9:
            // Your code for TIMER_9
            return (uint32_t)TIM9;
#endif

#ifdef HAVE_TIMER10
        case TIMER_10:
            // Your code for TIMER_10
            return (uint32_t)TIM10;
#endif

#ifdef HAVE_TIMER11
        case TIMER_11:
            // Your code for TIMER_11
            return (uint32_t)TIM11;
#endif

#ifdef HAVE_TIMER12
        case TIMER_12:
            // Your code for TIMER_12
            return (uint32_t)TIM12;
#endif

#ifdef HAVE_TIMER13
        case TIMER_13:
            // Your code for TIMER_13
            return (uint32_t)TIM13;
#endif

#ifdef HAVE_TIMER14
        case TIMER_14:
            // Your code for TIMER_14
            return (uint32_t)TIM14;
#endif

        case TIMER_END:
            // Placeholder for unused case
            break;
    }
    return 0;
}