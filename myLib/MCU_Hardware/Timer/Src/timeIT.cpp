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
uint8_t g_timxchy_cap_sta = 0;    /* 输入捕获状态 */
uint16_t g_timxchy_cap_val = 0;   /* 输入捕获值 */
uint8_t CurrentCaptureTimer=0;           /*当前输入捕获定时器的标志*/
uint8_t CurrentCaptureTimerChannel=0; /*当前输入捕获定时器选择的通道*/
uint32_t g_timxchy_cnt_ofcnt=0;     /* 计数溢出次数 */
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
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == BaseTimeValue.TIMEList[CurrentCaptureTimer].Instance) {
        if ((g_timxchy_cap_sta & 0x80) == 0)    /* 还未成功捕获 */
        {
            if (g_timxchy_cap_sta & 0x40)       /* 捕获到一个下降沿 */
            {
                g_timxchy_cap_sta |= 0x80;      /* 标记成功捕获到一次高电平脉宽 */
                g_timxchy_cap_val = HAL_TIM_ReadCapturedValue(&BaseTimeValue.TIMEList[CurrentCaptureTimer],
                                                              CurrentCaptureTimerChannel);  /* 获取当前的捕获值 */
                TIM_RESET_CAPTUREPOLARITY(&BaseTimeValue.TIMEList[CurrentCaptureTimer],
                                          CurrentCaptureTimerChannel);                      /* 一定要先清除原来的设置 */
                TIM_SET_CAPTUREPOLARITY(&BaseTimeValue.TIMEList[CurrentCaptureTimer], CurrentCaptureTimerChannel,
                                        TIM_ICPOLARITY_RISING); /* 配置TIM5通道1上升沿捕获 */
            } else                                            /* 还未开始,第一次捕获上升沿 */
            {
                g_timxchy_cap_sta = 0;                      /* 清空 */
                g_timxchy_cap_val = 0;
                g_timxchy_cap_sta |= 0x40;                  /* 标记捕获到了上升沿 */
                __HAL_TIM_DISABLE(&BaseTimeValue.TIMEList[CurrentCaptureTimer]);  /* 关闭定时器5 */
                __HAL_TIM_SET_COUNTER(&BaseTimeValue.TIMEList[CurrentCaptureTimer], 0);  /* 定时器5计数器清零 */
                TIM_RESET_CAPTUREPOLARITY(&BaseTimeValue.TIMEList[CurrentCaptureTimer],
                                          CurrentCaptureTimerChannel);                       /* 一定要先清除原来的设置！！ */
                TIM_SET_CAPTUREPOLARITY(&BaseTimeValue.TIMEList[CurrentCaptureTimer], CurrentCaptureTimerChannel,
                                        TIM_ICPOLARITY_FALLING); /* 定时器5通道1设置为下降沿捕获 */
                __HAL_TIM_ENABLE(
                        &BaseTimeValue.TIMEList[CurrentCaptureTimer]);                                                   /* 使能定时器5 */
            }
        }
    }
}
void CaptureStatusSwitch(){
    if ((g_timxchy_cap_sta & 0X80) == 0) /* 还没成功捕获 */
    {
        if (g_timxchy_cap_sta & 0X40) /* 已经捕获到高电平了 */
        {
            if ((g_timxchy_cap_sta & 0X3F) == 0X3F) /* 高电平太长了 */
            {
                TIM_RESET_CAPTUREPOLARITY(&BaseTimeValue.TIMEList[CurrentCaptureTimer], CurrentCaptureTimerChannel); /* 一定要先清除原来的设置 */
/* 配置 TIM5 通道 1 上升沿捕获 */
                TIM_SET_CAPTUREPOLARITY(&BaseTimeValue.TIMEList[CurrentCaptureTimer], CurrentCaptureTimerChannel, TIM_ICPOLARITY_RISING);
                g_timxchy_cap_sta |= 0X80; /* 标记成功捕获了一次 */
                g_timxchy_cap_val = 0XFFFF;
            }
            else /* 累计定时器溢出次数 */
            {
                g_timxchy_cap_sta++;
            }
        }
    }
}
void CounterPulseNum(){
    g_timxchy_cnt_ofcnt++;
}