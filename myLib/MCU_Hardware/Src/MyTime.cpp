/**
*********************************************************************
*********
* @project_name :car0
* @file : MyTime.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/10
*********************************************************************
*********
*/
//

#include "MyTime.h"
#include "MyGPIO.h"
using CallBack = void(*)(void);
MyGPIO myGPIOTime;

uint8_t SaveTime[MAXTIMNUM]={0};
uint32_t g_timxchy_cnt_ofcnt = 0 ;              /* 计数溢出次数 */
struct TimeInfo{
    TIM_HandleTypeDef TIMEList[MAXTIMNUM];//全局定时器句柄
    TIM_HandleTypeDef PWMTIMList[MAXTIMNUM];
    TIM_HandleTypeDef CaptureTIMList[MAXTIMNUM];
    TIM_HandleTypeDef CounterTimList[MAXTIMNUM];
    uint8_t TIMExPWM_Channel[MAXTIMNUM];
    uint8_t TIMExCapture_Channel[MAXTIMNUM];
    uint8_t TIMEx_IRQn[MAXTIMNUM];
}timeInfo;
//static TimeInfo timeInfo={0};
static CallBack TimeExit[MAXTIMNUM];
void MyTime::timer_BasicTimerInit(Timer_enum timer, uint32_t arr, uint32_t psc) {
    OpenRccTime(timer);
    timeInfo.TIMEx_IRQn[timer]= getTIMEx_IRQn(timer);
    HAL_NVIC_SetPriority((IRQn_Type)timeInfo.TIMEx_IRQn[timer],1,3);
    HAL_NVIC_EnableIRQ((IRQn_Type)timeInfo.TIMEx_IRQn[timer]);
    timeInfo.TIMEList[timer].Instance= ( TIM_TypeDef*)getTimeInstance(timer);
    timeInfo.TIMEList[timer].Init.Prescaler=psc;
    timeInfo.TIMEList[timer].Init.CounterMode=TIM_COUNTERMODE_UP;
    timeInfo.TIMEList[timer].Init.Period=arr;
    HAL_TIM_Base_Init(&timeInfo.TIMEList[timer]);
    HAL_TIM_Base_Start_IT(&timeInfo.TIMEList[timer]);
}

void MyTime::timer_GenericTimerInit(Timer_enum timer, uint32_t arr, uint32_t psc, GenericTIMMode genericMode) {
    OpenRccTime(timer);
    switch (genericMode.genericMode) {
        case GenericMode::TIME_PWM:
            timer_PWMCHYInit(timer,arr,psc,genericMode);
            break;
        case GenericMode::TIME_Capture:
            timer_CaptureCHInit(timer,arr,psc,genericMode);
            break;
        case GenericMode::TIME_PulseCounting:
            timer_CounterPluseInit(timer,arr,psc,genericMode);
            break;
        default:
            break;
    }
}

void MyTime::timer_AdvancedTimerInit(Timer_enum timer, uint32_t arr, uint32_t psc, AdvancedTIMMode advancedMode) {

}

void MyTime::timer_start(Timer_enum timer) {
    HAL_TIM_Base_Start_IT(&timeInfo.TIMEList[timer]);
}

void MyTime::timer_stop(Timer_enum timer) {
    HAL_TIM_Base_Stop_IT(&timeInfo.TIMEList[timer]);
}

void MyTime::timer_reset(Timer_enum timer) {
    HAL_TIM_Base_DeInit(&timeInfo.TIMEList[timer]);
}

bool MyTime::timer_is_running(Timer_enum timer) {
    auto timerFlag = __HAL_TIM_GET_FLAG(&timeInfo.TIMEList[timer], TIM_FLAG_UPDATE);
    return timerFlag;
}

uint32_t MyTime::timer_getCurrentValue(Timer_enum timer) {
    uint32_t prescalerValue = timeInfo.TIMEList[timer].Init.Prescaler + 1; // 实际的预分频值

    // 获取定时器的当前计数值（包含预分频）
    uint32_t currentCounterValue = timeInfo.TIMEList[timer].Instance->CNT * prescalerValue;

    return currentCounterValue;
}

uint32_t MyTime::timer_getPeriod(Timer_enum timer) {
    uint32_t prescalerValue = timeInfo.TIMEList[timer].Init.Prescaler + 1; // 实际的预分频值

    // 获取定时器的周期值（包含预分频）
    uint32_t timerPeriod = (timeInfo.TIMEList[timer].Init.Period + 1) * prescalerValue;

    return timerPeriod;
}

uint32_t MyTime::timer_getRemainingTime(Timer_enum timer) {
    uint32_t prescalerValue = timeInfo.TIMEList[timer].Init.Prescaler + 1; // 实际的预分频值

    // 获取当前定时器计数值（包含预分频）
    uint32_t currentCounterValue = timeInfo.TIMEList[timer].Instance->CNT * prescalerValue;

    // 获取定时器的周期值（包含预分频）
    uint32_t timerPeriod = (timeInfo.TIMEList[timer].Init.Period + 1) * prescalerValue;

    // 计算距离下一次触发的剩余时间
    uint32_t remainingTime = timerPeriod - currentCounterValue;

    return remainingTime;
}

void MyTime::timer_set_callback(Timer_enum timer,CallBack callBack) {
    TimeExit[timer]=callBack;
}

void MyTime::timer_clear_callback(Timer_enum timer) {
    TimeExit[timer]= nullptr;
}
void TIM1_BRK_TIM9_IRQHandler(void) { HAL_TIM_IRQHandler(&timeInfo.TIMEList[0]);
                                      HAL_TIM_IRQHandler(&timeInfo.TIMEList[8]);}
void TIM1_UP_TIM10_IRQHandler(void) { HAL_TIM_IRQHandler(&timeInfo.TIMEList[9]); }
void TIM1_TRG_COM_TIM11_IRQHandler(void){HAL_TIM_IRQHandler(&timeInfo.TIMEList[10]);  }
void TIM2_IRQHandler(void) {HAL_TIM_IRQHandler(&timeInfo.TIMEList[1]);   }
void TIM3_IRQHandler(void) {HAL_TIM_IRQHandler(&timeInfo.TIMEList[2]);   }
void TIM4_IRQHandler(void) {HAL_TIM_IRQHandler(&timeInfo.TIMEList[3]);   }
void TIM5_IRQHandler(void) {HAL_TIM_IRQHandler(&timeInfo.TIMEList[4]);   } 
void TIM6_DAC_IRQHandler(void){HAL_TIM_IRQHandler(&timeInfo.TIMEList[5]);}
void TIM7_IRQHandler(void){HAL_TIM_IRQHandler(&timeInfo.TIMEList[6]); }
void TIM8_BRK_TIM12_IRQHandler(void) { HAL_TIM_IRQHandler(&timeInfo.TIMEList[7]);
                                       HAL_TIM_IRQHandler(&timeInfo.TIMEList[11]); }
void TIM8_UP_TIM13_IRQHandler(void) { HAL_TIM_IRQHandler(&timeInfo.TIMEList[12]);  }
void TIM8_TRG_COM_TIM14_IRQHandler(void) {  HAL_TIM_IRQHandler(&timeInfo.TIMEList[13]); }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if(htim->Instance==TIM1){
        if (TimeExit[0])
        TimeExit[0]();
        return;
    }
    if (htim->Instance==TIM2){
        if (TimeExit[1])
        TimeExit[1]();
        return;
    }
    if (htim->Instance==TIM3){
        if (TimeExit[2])
        TimeExit[2]();
        return;
    }
    if (htim->Instance==TIM4){
        if (TimeExit[3])
        TimeExit[3]();
        return;
    }
    if (htim->Instance==TIM5){
        if (TimeExit[4])
        TimeExit[4]();
        return;
    }
    if (htim->Instance==TIM6){
        if (TimeExit[5])
        TimeExit[5]();
        return;
    }
    if (htim->Instance==TIM7){
        if (TimeExit[6])
            TimeExit[6]();
        return;
    }
    if (htim->Instance==TIM8){
        if (TimeExit[7])
            TimeExit[7]();
        return;
    }
    if (htim->Instance==TIM9){
        if (TimeExit[8])
            TimeExit[8]();
        return;
    }
    if (htim->Instance==TIM10){
        if (TimeExit[9])
            TimeExit[9]();
        return;
    }
    if (htim->Instance==TIM11){
        if (TimeExit[10])
            TimeExit[10]();
        return;
    }
    if (htim->Instance==TIM12){
        if (TimeExit[11])
            TimeExit[11]();
        return;
    }
    if (htim->Instance==TIM13){
        if (TimeExit[12])
            TimeExit[12]();
        return;
    } if (htim->Instance==TIM14){
        if (TimeExit[13])
            TimeExit[13]();
        return;
    }
}

void MyTime::OpenRccTime(Timer_enum timer) {
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

uint8_t MyTime::getTIMEx_IRQn(Timer_enum timer) {
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

uint32_t MyTime::getTimeInstance(Timer_enum timer) {
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

void MyTime::timer_PWMCHYInit(Timer_enum timer, uint32_t arr, uint32_t psc, GenericTIMMode genericMode) {
    myGPIOTime.gpio_init(genericMode.pwmChannelIO,GpioMode::af_pp,GpioPull::pullup,genericMode.alternateMode);
    timeInfo.PWMTIMList[timer].Instance= (TIM_TypeDef*)getTimeInstance(timer);
    timeInfo.PWMTIMList[timer].Init.Prescaler=psc;
    timeInfo.PWMTIMList[timer].Init.CounterMode=TIM_COUNTERMODE_UP;
    timeInfo.PWMTIMList[timer].Init.Period=arr;
    HAL_TIM_PWM_Init(&timeInfo.PWMTIMList[timer]);
    TIM_OC_InitTypeDef timx_oc_pwm_chy = {0};                       /* 定时器输出句柄 */
    timx_oc_pwm_chy.OCMode = TIM_OCMODE_PWM1;                       /* 模式选择PWM1 */
    timx_oc_pwm_chy.Pulse = arr / 2;                                /* 设置比较值,此值用来确定占空比 */
    timx_oc_pwm_chy.OCPolarity = TIM_OCPOLARITY_LOW;
    HAL_TIM_PWM_ConfigChannel(&timeInfo.PWMTIMList[timer], &timx_oc_pwm_chy,genericMode.Tim_Channel); /* 配置TIMx通道y */
    HAL_TIM_PWM_Start(&timeInfo.PWMTIMList[timer],genericMode.Tim_Channel);
}

uint32_t MyTime::pwm_getFrequency(Timer_enum timer) const {

    uint32_t getPclk1Freq=HAL_RCC_GetPCLK2Freq()/(timeInfo.PWMTIMList[timer].Init.Prescaler+1)/
            (timeInfo.PWMTIMList[timer].Init.Period+1);
    return getPclk1Freq;
}

float MyTime::pwm_getDutyCycle(Timer_enum timer, GenericTIMMode genericMode) const {

    float periodValue= __HAL_TIM_GET_AUTORELOAD(&timeInfo.PWMTIMList[timer]);
    float PulseValue=timeInfo.PWMTIMList[timer].Instance->CCR1;
    auto dutyCycle=(float)(PulseValue/periodValue)*100;
    return dutyCycle;
}

void MyTime::pwm_setPhase(Timer_enum timer, float phase, GenericTIMMode genericMode) {
    // 获取定时器的自动重装载寄存器值
    uint32_t periodValue = __HAL_TIM_GET_AUTORELOAD(&timeInfo.PWMTIMList[timer]);

    // 计算相位对应的比较值
    uint32_t phaseValue = (uint32_t)((phase / 360.0) * periodValue);
    __HAL_TIM_SET_COMPARE(&timeInfo.PWMTIMList[timer],genericMode.Tim_Channel,phaseValue);

}

void MyTime::pwm_setPulseWidth(Timer_enum timer, uint32_t pulse_width, GenericTIMMode genericMode) {
    this->pwm_set_duty_cycle(timer,pulse_width,genericMode);
}

void MyTime::pwm_start(Timer_enum timer, GenericTIMMode genericMode) {
    HAL_TIM_PWM_Start(&timeInfo.PWMTIMList[timer],genericMode.Tim_Channel);
}

void MyTime::pwm_stop(Timer_enum timer, GenericTIMMode genericMode) {
    HAL_TIM_PWM_Stop(&timeInfo.PWMTIMList[timer],genericMode.Tim_Channel);
}

void MyTime::pwm_set_duty_cycle(Timer_enum timer, uint16_t duty_cycle, GenericTIMMode genericMode) {
    __HAL_TIM_SetCompare(&timeInfo.PWMTIMList[timer],genericMode.Tim_Channel,duty_cycle);
}

void MyTime::pwm_setInterruptCallback(Timer_enum timer, void (*callback)(void), GenericTIMMode genericMode) {

}
void Timer_input_capture_interrupt_handling_callback_function();
void MyTime::timer_CaptureCHInit(Timer_enum timer, uint32_t arr, uint32_t psc, GenericTIMMode mode) {
    TIM_IC_InitTypeDef timIcInitTypeDef;
    myGPIOTime.gpio_init(mode.CaptureChannelIO,GpioMode::af_pp,GpioPull::pulldown,mode.alternateMode);
    uint8_t IC_IRQn= getTIMEx_IRQn(timer);
    HAL_NVIC_SetPriority((IRQn_Type)IC_IRQn, 1, 3);         /* 抢占1，子优先级3 */
    HAL_NVIC_EnableIRQ((IRQn_Type)IC_IRQn);                 /* 开启ITMx中断 */
    timeInfo.CaptureTIMList[timer].Instance = (TIM_TypeDef*)getTimeInstance(timer);
    timeInfo.CaptureTIMList[timer].Init.Prescaler = psc;
    timeInfo.CaptureTIMList[timer].Init.CounterMode = TIM_COUNTERMODE_UP;
    timeInfo.CaptureTIMList[timer].Init.Period = arr;
    HAL_TIM_IC_Init(&timeInfo.CaptureTIMList[timer]);
    timIcInitTypeDef.ICPolarity = TIM_ICPOLARITY_RISING;
    timIcInitTypeDef.ICSelection = TIM_ICSELECTION_DIRECTTI;
    timIcInitTypeDef.ICPrescaler=TIM_ICPSC_DIV1;
    timIcInitTypeDef.ICFilter=0;
    this->timer_set_callback(timer,Timer_input_capture_interrupt_handling_callback_function);
    timeInfo.TIMExCapture_Channel[timer]=mode.Tim_CaptureChannel;
    SaveTime[timer]=(uint8_t)timer;
    HAL_TIM_IC_ConfigChannel(&timeInfo.CaptureTIMList[timer],&timIcInitTypeDef,(uint32_t)mode.Tim_CaptureChannel);
    __HAL_TIM_ENABLE_IT(&timeInfo.CaptureTIMList[timer], TIM_IT_UPDATE);         /* 使能更新中断 */
    HAL_TIM_IC_Start_IT(&timeInfo.CaptureTIMList[timer], mode.Tim_CaptureChannel);     /* 开始捕获TIM5的通道1 */

}
uint8_t g_timxchy_cap_sta = 0;    /* 输入捕获状态 */
uint16_t g_timxchy_cap_val = 0;   /* 输入捕获值 */
uint32_t MyTime::CaptureHighLevelTime() {
    uint32_t temp=0;
    if (g_timxchy_cap_sta & 0x80)           /* 成功捕获到了一次高电平 */
    {
        temp = g_timxchy_cap_sta & 0x3F;
        temp *= 0xFFFF;                     /* 溢出时间总和 */
        temp += g_timxchy_cap_val;          /* 得到总的高电平时间 */
        g_timxchy_cap_sta = 0;              /* 开启下一次捕获 */
    }
    return temp;
}

void MyTime::timer_CounterPluseInit(Timer_enum timer, uint32_t arr, uint32_t psc, GenericTIMMode mode) {
    myGPIOTime.gpio_init(mode.CounterChannelIO,GpioMode::af_pp,GpioPull::pulldown,mode.alternateMode);
    timeInfo.CounterTimList[timer]
    TIM_SlaveConfigTypeDef tim_slave_config = {0};

}

/**
 * @brief       定时器输入捕获中断处理回调函数
 * @param       htim:定时器句柄指针
 * @note        该函数在HAL_TIM_IRQHandler中会被调用
 * @retval      无
 */

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    for (unsigned char i : SaveTime) {
        if (i!=0) {

            if ((g_timxchy_cap_sta & 0x80) == 0)    /* 还未成功捕获 */
            {
                if (g_timxchy_cap_sta & 0x40)       /* 捕获到一个下降沿 */
                {
                    g_timxchy_cap_sta |= 0x80;      /* 标记成功捕获到一次高电平脉宽 */
                    g_timxchy_cap_val = HAL_TIM_ReadCapturedValue(&timeInfo.CaptureTIMList[i],
                                                                  timeInfo.TIMExCapture_Channel[i]);  /* 获取当前的捕获值 */
                    TIM_RESET_CAPTUREPOLARITY(&timeInfo.CaptureTIMList[i],
                                              timeInfo.TIMExCapture_Channel[i]);                      /* 一定要先清除原来的设置 */
                    TIM_SET_CAPTUREPOLARITY(&timeInfo.CaptureTIMList[i],
                                            timeInfo.TIMExCapture_Channel[i],
                                            TIM_ICPOLARITY_RISING); /* 配置TIM5通道1上升沿捕获 */
                } else                                            /* 还未开始,第一次捕获上升沿 */
                {
                    g_timxchy_cap_sta = 0;                      /* 清空 */
                    g_timxchy_cap_val = 0;
                    g_timxchy_cap_sta |= 0x40;                  /* 标记捕获到了上升沿 */
                    __HAL_TIM_DISABLE(&timeInfo.CaptureTIMList[i]);  /* 关闭定时器5 */
                    __HAL_TIM_SET_COUNTER(&timeInfo.CaptureTIMList[i], 0);  /* 定时器5计数器清零 */
                    TIM_RESET_CAPTUREPOLARITY(&timeInfo.CaptureTIMList[i],
                                              timeInfo.TIMExCapture_Channel[i]);                       /* 一定要先清除原来的设置！！ */
                    TIM_SET_CAPTUREPOLARITY(&timeInfo.CaptureTIMList[i],
                                            timeInfo.TIMExCapture_Channel[i],
                                            TIM_ICPOLARITY_FALLING); /* 定时器5通道1设置为下降沿捕获 */
                    __HAL_TIM_ENABLE(&timeInfo.CaptureTIMList[i]);                                                   /* 使能定时器5 */
                }
            }
        }
    }
}


void Timer_input_capture_interrupt_handling_callback_function() {
    for (unsigned char i: SaveTime) {
        if (i != 0) {
            if ((g_timxchy_cap_sta & 0x80) == 0)    /* 还未成功捕获 */
            {
                if (g_timxchy_cap_sta & 0x40)       /* 捕获到一个下降沿 */
                {
                    g_timxchy_cap_sta |= 0x80;      /* 标记成功捕获到一次高电平脉宽 */
                    g_timxchy_cap_val = HAL_TIM_ReadCapturedValue(&timeInfo.CaptureTIMList[SaveTime[i]],
                                                                  timeInfo.TIMExCapture_Channel[SaveTime[i]]);  /* 获取当前的捕获值 */
                    TIM_RESET_CAPTUREPOLARITY(&timeInfo.CaptureTIMList[SaveTime[i]],
                                              timeInfo.TIMExCapture_Channel[SaveTime[i]]);                      /* 一定要先清除原来的设置 */
                    TIM_SET_CAPTUREPOLARITY(&timeInfo.CaptureTIMList[SaveTime[i]],
                                            timeInfo.TIMExCapture_Channel[SaveTime[i]],
                                            TIM_ICPOLARITY_RISING); /* 配置TIM5通道1上升沿捕获 */
                } else                                            /* 还未开始,第一次捕获上升沿 */
                {
                    g_timxchy_cap_sta = 0;                      /* 清空 */
                    g_timxchy_cap_val = 0;
                    g_timxchy_cap_sta |= 0x40;                  /* 标记捕获到了上升沿 */
                    __HAL_TIM_DISABLE(&timeInfo.CaptureTIMList[SaveTime[i]]);  /* 关闭定时器5 */
                    __HAL_TIM_SET_COUNTER(&timeInfo.CaptureTIMList[SaveTime[i]], 0);  /* 定时器5计数器清零 */
                    TIM_RESET_CAPTUREPOLARITY(&timeInfo.CaptureTIMList[SaveTime[i]],
                                              timeInfo.TIMExCapture_Channel[SaveTime[i]]);                       /* 一定要先清除原来的设置！！ */
                    TIM_SET_CAPTUREPOLARITY(&timeInfo.CaptureTIMList[SaveTime[i]],
                                            timeInfo.TIMExCapture_Channel[SaveTime[i]],
                                            TIM_ICPOLARITY_FALLING); /* 定时器5通道1设置为下降沿捕获 */
                    __HAL_TIM_ENABLE(&timeInfo.CaptureTIMList[SaveTime[i]]);                                                   /* 使能定时器5 */
                }
            }
        }
    }
}