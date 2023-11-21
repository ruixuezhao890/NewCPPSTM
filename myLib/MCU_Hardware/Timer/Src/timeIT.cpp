/**
*********************************************************************
*********
* @project_name :car0
* @file : timeIT.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/20 
*********************************************************************
*********
*/
//

#include "timeIT.h"
#include "virTime.h"
#include "stm32f4xx.h"
void TIM1_BRK_TIM9_IRQHandler(void) { HAL_TIM_IRQHandler(&BaseTimeValue.TIMEList[0]);
    HAL_TIM_IRQHandler(&BaseTimeValue.TIMEList[8]);}
void TIM1_UP_TIM10_IRQHandler(void) { HAL_TIM_IRQHandler(&BaseTimeValue.TIMEList[9]); }
void TIM1_TRG_COM_TIM11_IRQHandler(void){HAL_TIM_IRQHandler(&BaseTimeValue.TIMEList[10]);  }
void TIM2_IRQHandler(void) {HAL_TIM_IRQHandler(&BaseTimeValue.TIMEList[1]);   }
void TIM3_IRQHandler(void) {HAL_TIM_IRQHandler(&BaseTimeValue.TIMEList[2]);   }
void TIM4_IRQHandler(void) {HAL_TIM_IRQHandler(&BaseTimeValue.TIMEList[3]);   }
void TIM5_IRQHandler(void) {HAL_TIM_IRQHandler(&BaseTimeValue.TIMEList[4]);   }
void TIM6_DAC_IRQHandler(void){HAL_TIM_IRQHandler(&BaseTimeValue.TIMEList[5]);}
void TIM7_IRQHandler(void){HAL_TIM_IRQHandler(&BaseTimeValue.TIMEList[6]); }
void TIM8_BRK_TIM12_IRQHandler(void) { HAL_TIM_IRQHandler(&BaseTimeValue.TIMEList[7]);
    HAL_TIM_IRQHandler(&BaseTimeValue.TIMEList[11]); }
void TIM8_UP_TIM13_IRQHandler(void) { HAL_TIM_IRQHandler(&BaseTimeValue.TIMEList[12]);  }
void TIM8_TRG_COM_TIM14_IRQHandler(void) {  HAL_TIM_IRQHandler(&BaseTimeValue.TIMEList[13]); }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if(htim->Instance==TIM1){
        if (ExitValue.TimeExit[0])
            ExitValue.TimeExit[0](ExitValue.arg[0]);
        if (OnceFlag[0]){
            HAL_TIM_Base_Stop_IT(&BaseTimeValue.TIMEList[0]);
        }
        return;
    }
    if (htim->Instance==TIM2){
        if (ExitValue.TimeExit[1])
            ExitValue.TimeExit[1](ExitValue.arg[1]);
        if (OnceFlag[1]){
            HAL_TIM_Base_Stop_IT(&BaseTimeValue.TIMEList[1]);
        }
        return;
    }
    if (htim->Instance==TIM3){
        if (ExitValue.TimeExit[2])
            ExitValue.TimeExit[2](ExitValue.arg[2]);
        if (OnceFlag[2]){
            HAL_TIM_Base_Stop_IT(&BaseTimeValue.TIMEList[2]);
        }
        return;
    }
    if (htim->Instance==TIM4){
        if (ExitValue.TimeExit[3])
            ExitValue.TimeExit[3](ExitValue.arg[3]);
        if (OnceFlag[3]){
            HAL_TIM_Base_Stop_IT(&BaseTimeValue.TIMEList[3]);
        }
        return;
    }
    if (htim->Instance==TIM5){
        if (ExitValue.TimeExit[4])
            ExitValue.TimeExit[4](ExitValue.arg[4]);
        if (OnceFlag[4]){
            HAL_TIM_Base_Stop_IT(&BaseTimeValue.TIMEList[4]);
        }
        return;
    }
    if (htim->Instance==TIM6){
        if (ExitValue.TimeExit[5])
            ExitValue.TimeExit[5](ExitValue.arg[5]);
        if (OnceFlag[5]){
            HAL_TIM_Base_Stop_IT(&BaseTimeValue.TIMEList[5]);
        }
        return;
    }
    if (htim->Instance==TIM7){
        if (ExitValue.TimeExit[6])
            ExitValue.TimeExit[6](ExitValue.arg[6]);
        if (OnceFlag[6]){
            HAL_TIM_Base_Stop_IT(&BaseTimeValue.TIMEList[6]);
        }
        return;
    }
    if (htim->Instance==TIM8){
        if (ExitValue.TimeExit[7])
            ExitValue.TimeExit[7](ExitValue.arg[7]);
        if (OnceFlag[7]){
            HAL_TIM_Base_Stop_IT(&BaseTimeValue.TIMEList[7]);
        }
        return;
    }
    if (htim->Instance==TIM9){
        if (ExitValue.TimeExit[8])
            ExitValue.TimeExit[8](ExitValue.arg[8]);
        if (OnceFlag[8]){
            HAL_TIM_Base_Stop_IT(&BaseTimeValue.TIMEList[8]);
        }
        return;
    }
    if (htim->Instance==TIM10){
        if (ExitValue.TimeExit[9])
            ExitValue.TimeExit[9](ExitValue.arg[9]);
        if (OnceFlag[9]){
            HAL_TIM_Base_Stop_IT(&BaseTimeValue.TIMEList[9]);
        }
        return;
    }
    if (htim->Instance==TIM11){
        if (ExitValue.TimeExit[10])
            ExitValue.TimeExit[10](ExitValue.arg[10]);
        if (OnceFlag[10]){
            HAL_TIM_Base_Stop_IT(&BaseTimeValue.TIMEList[10]);
        }
        return;
    }
    if (htim->Instance==TIM12){
        if (ExitValue.TimeExit[11])
            ExitValue.TimeExit[11](ExitValue.arg[11]);
        if (OnceFlag[11]){
            HAL_TIM_Base_Stop_IT(&BaseTimeValue.TIMEList[11]);
        }
        return;
    }
    if (htim->Instance==TIM13){
        if (ExitValue.TimeExit[12])
            ExitValue.TimeExit[12](ExitValue.arg[12]);
        if (OnceFlag[12]){
            HAL_TIM_Base_Stop_IT(&BaseTimeValue.TIMEList[12]);
        }
        return;
    } if (htim->Instance==TIM14){
        if (ExitValue.TimeExit[13])
            ExitValue.TimeExit[13](ExitValue.arg[13]);
        if (OnceFlag[13]){
            HAL_TIM_Base_Stop_IT(&BaseTimeValue.TIMEList[13]);
        }
        return;
    }
}
