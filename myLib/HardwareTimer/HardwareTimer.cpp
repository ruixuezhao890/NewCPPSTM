/*
  Copyright (c) 2017 Daniel Fekete

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

  Copyright (c) 2019 STMicroelectronics
  Modified to support Arduino_Core_STM32
*/

//#include "Arduino.h"
#include "HardwareTimer.h"
#include "TimerRes.h"
#include "stm32f4xx_ll_tim.h"
#include "MyUsart.h"
#include "gpio.h"
#include "tim.h"

#ifdef HAL_TIM_MODULE_ENABLED

/* Private Defines */
#define PIN_NOT_USED 0xFF
#define MAX_RELOAD ((1 << 16) - 1) // Currently even 32b timers are used as 16b to have generic behavior

/* Private Variables */


/**
  * @brief  HardwareTimer constructor: make uninitialized timer
  *         Before calling any methods, call setup to select and setup
  *         the timer to be used.
  * @retval None
  */
HardwareTimer::HardwareTimer()
{

}

/**
  * @brief  HardwareTimer constructor: set default configuration values
  *         The timer will be usable directly, there is no need to call
  *         setup(). Using this constructor is not recommended for
  *         global variables that are automatically initialized at
  *         startup, since this will happen to early to report any
  *         errors. Better use the argumentless constructor and call the
  *         setup() method during initialization later.
  * @param  Timer instance ex: TIM1, ...
  * @retval None
  */
HardwareTimer::HardwareTimer(TIM_HandleTypeDef *instance)
{
    setup(instance);
}

/**
  * @brief  HardwareTimer setup: configuration values. Must be called
  * exactly once before any other methods, except when an instance is
  * passed to the constructor.
  * @param  Timer instance ex: TIM1, ...
  * @retval None
  */
void HardwareTimer::setup(TIM_HandleTypeDef *instance)
{
  this->timer=instance;
}

/**
  * @brief  Pause HardwareTimer: stop timer
  * @param  None
  * @retval None
  */
void HardwareTimer::pause()
{
  // Disable all IT
  __HAL_TIM_DISABLE_IT(this->timer, TIM_IT_UPDATE);
  __HAL_TIM_DISABLE_IT(this->timer, TIM_IT_CC1);
  __HAL_TIM_DISABLE_IT(this->timer, TIM_IT_CC2);
  __HAL_TIM_DISABLE_IT(this->timer, TIM_IT_CC3);
  __HAL_TIM_DISABLE_IT(this->timer, TIM_IT_CC4);

  // Stop timer. Required to restore HAL State: HAL_TIM_STATE_READY
  HAL_TIM_Base_Stop(this->timer);

  /* Disable timer unconditionally. Required to guarantee timer is stopped,
   * even if some channels are still running */
  LL_TIM_DisableCounter(this->timer->Instance);

#if defined(TIM_CHANNEL_STATE_SET_ALL)
  /* Starting from G4, new Channel state implementation prevents to restart a channel,
     if the channel has not been explicitly be stopped with HAL interface */
  TIM_CHANNEL_STATE_SET_ALL(this->timer, HAL_TIM_CHANNEL_STATE_READY);
#endif
#if defined(TIM_CHANNEL_N_STATE_SET_ALL)
  TIM_CHANNEL_N_STATE_SET_ALL(this->timer, HAL_TIM_CHANNEL_STATE_READY);
#endif
}

/**
  * @brief  Pause only one channel.
  *         Timer is still running but channel is disabled (output and interrupt)
  * @param  Arduino channel [1..4]
  * @retval None
  */
void HardwareTimer::pauseCapture(uint32_t Channel)
{
    int channel= getChannel(Channel);
    if (callbacksCaptureCompare[0])
    HAL_TIM_PWM_Stop_IT(this->timer,channel);
    else
        HAL_TIM_PWM_Stop(this->timer,channel);
}

/**
  * @brief  Start or resume HardwareTimer: all channels are resumed, interrupts are enabled if necessary
  * @param  None
  * @retval None
  */
void HardwareTimer::resume(void) {

    // Clear flag and enable IT
    if (callbacks[0]) {
        HAL_TIM_Base_Start_IT(this->timer);
    } else {
        HAL_TIM_Base_Start(this->timer);
        {

//            // Resume all channels
//            resumeCapture(1);
//            resumeCapture(2);
//            resumeCapture(3);
//            resumeCapture(4);
        }
    }
}
void HardwareTimer::resumeCapture(uint32_t Channel) {
    if(!Channel) {
        Serial0.println("error");
        return ;
    }else {
        int channel= getChannel(Channel);
        if (callbacksCaptureCompare[0])
            HAL_TIM_PWM_Start_IT(this->timer, channel);
        else
            HAL_TIM_PWM_Start(this->timer, channel);
    }
}

void HardwareTimer::pauseOutputCompare(uint32_t Channel) {
    if (!Channel) {
        Serial0.print("error");
        return;
    }
    int channel= getChannel(Channel);
    if (callbacksCaptureCompare[0]) {
        HAL_TIM_IC_Stop_IT(this->timer, channel);
    } else {
        HAL_TIM_IC_Stop(this->timer, channel);
    }
}

void HardwareTimer::resumeOutputCompare(uint32_t Channel) {
    if (!Channel) {
        Serial0.print("error");
        return;
    }
    int channel= getChannel(Channel);
    if (callbacksCaptureCompare[0]) {
        HAL_TIM_IC_Start_IT(this->timer, channel);
    } else {
        HAL_TIM_IC_Start(this->timer, channel);
    }
}
/**
  * @brief  Attach interrupt callback on update (rollover) event
  * @param  callback: interrupt callback
  * @retval None
  */
void HardwareTimer::attachInterrupt(callback_function_t callback)
{
  if (callbacks[0]) {
    // Callback previously configured : do not clear neither enable IT, it is just a change of callback
    callbacks[0] = callback;
  } else {
    callbacks[0] = callback;
    if (callback) {
      // Clear flag before enabling IT
      __HAL_TIM_CLEAR_FLAG(this->timer, TIM_FLAG_UPDATE);
      // Enable update interrupt only if callback is valid
      __HAL_TIM_ENABLE_IT(this->timer, TIM_IT_UPDATE);
    }
  }
}

/**
  * @brief  Detach interrupt callback on update (rollover) event
  * @retval None
  */
void HardwareTimer::detachInterrupt()
{
  // Disable update interrupt and clear callback
  __HAL_TIM_DISABLE_IT(this->timer, TIM_IT_UPDATE); // disables the interrupt call to save cpu cycles for useless context switching
  callbacks[0] = nullptr;
}

/**
  * @brief  Attach interrupt callback on Capture/Compare event
  * @param  channel: Arduino channel [1..4]
  * @param  callback: interrupt callback
  * @retval None
  */
void HardwareTimer::attachInterrupt(uint32_t channel, callback_function_t callback)
{
    if (!channel) {
        Serial0.print("error");
        return;
    }
  int interrupt = getIT(channel);
  if (interrupt == -1) {
    Error_Handler();
  }

  if ((channel == 0) || (channel > (TIMER_CHANNELS + 1))) {
    Error_Handler();  // only channel 1..4 have an interrupt
  }
  if (callbacksCaptureCompare[channel]) {
    // Callback previously configured : do not clear neither enable IT, it is just a change of callback
      callbacksCaptureCompare[channel] = callback;
  } else {
      callbacksCaptureCompare[channel] = callback;
    if (callback) {
      // Clear flag before enabling IT
      __HAL_TIM_CLEAR_FLAG(this->timer, interrupt);
      // Enable interrupt corresponding to channel, only if callback is valid
      __HAL_TIM_ENABLE_IT(this->timer, interrupt);
    }
  }
}

/**
  * @brief  Detach interrupt callback on Capture/Compare event
  * @param  channel: Arduino channel [1..4]
  * @retval None
  */
void HardwareTimer::detachInterrupt(uint32_t channel)
{
    if (!channel) {
        Serial0.print("error");
        return;
    }
  int interrupt = getIT(channel);
  if (interrupt == -1) {
    Error_Handler();
  }

  if ((channel == 0) || (channel > (TIMER_CHANNELS + 1))) {
    Error_Handler();  // only channel 1..4 have an interrupt
  }

  // Disable interrupt corresponding to channel and clear callback
  __HAL_TIM_DISABLE_IT(this->timer, interrupt);
    callbacksCaptureCompare[channel] = nullptr;
}

/**
  * @brief  Checks if there's an interrupt callback attached on Rollover event
  * @retval returns true if a timer rollover interrupt has already been set
  */
bool HardwareTimer::hasInterrupt()
{
  return callbacks[0] != nullptr;
}

/**
  * @brief  Checks if there's an interrupt callback attached on Capture/Compare event
  * @param  channel: Arduino channel [1..4]
  * @retval returns true if a channel compare match interrupt has already been set
  */
bool HardwareTimer::hasInterrupt(uint32_t channel)
{
    if (!channel) {
        Serial0.print("error");
        return false;
    }
  if ((channel == 0) || (channel > (TIMER_CHANNELS + 1))) {
    Error_Handler();  // only channel 1..4 have an interrupt
  }
  return callbacks[channel] != nullptr;
}

/**
  * @brief  Generate an update event to force all registers (Autoreload, prescaler, compare) to be taken into account
  * @note   @note Refresh() can only be called after timer has been initialized,
            either by calling setup() function or thanks to constructor with TIM instance parameter.
  *         It is useful while timer is running after some registers update
  * @retval None
  */
void HardwareTimer::refresh()
{
  HAL_TIM_GenerateEvent(this->timer, TIM_EVENTSOURCE_UPDATE);
}

/**
  * @brief  Return the timer object handle object for more advanced setup
  * @note   Using this function and editing the Timer handle is at own risk! No support will
  *         be provided whatsoever if the HardwareTimer does not work as expected when editing
  *         the handle using the HAL functionality or other custom coding.
  * @retval TIM_HandleTypeDef address
  */
TIM_HandleTypeDef *HardwareTimer::getHandle()
{
  return this->timer;
}

/**
  * @brief  Generic Update (rollover) callback which will call user callback
  * @param  htim: HAL timer handle
  * @retval None
  */
void HardwareTimer::updateCallback(TIM_HandleTypeDef *htim)
{
  if (!htim) {
    Error_Handler();
  }

//  timerObj_t *obj = get_timer_obj(htim);
//  HardwareTimer *HT = (HardwareTimer *)(obj->__this);
    HardwareTimer *HT= getTimerOOP(htim);
    if (HT->callbacks[0]) {
    HT->callbacks[0]();
  }
}

/**
  * @brief  Generic Capture and Compare callback which will call user callback
  * @param  htim: HAL timer handle
  * @retval None
  */
void HardwareTimer::captureCompareCallback(TIM_HandleTypeDef *htim)
{
  if (!htim) {
      return;
  }
  uint32_t channel = htim->Channel;

  switch (htim->Channel) {
    case HAL_TIM_ACTIVE_CHANNEL_1: {
        channel = 1;
        break;
      }
    case HAL_TIM_ACTIVE_CHANNEL_2: {
        channel = 2;
        break;
      }
    case HAL_TIM_ACTIVE_CHANNEL_3: {
        channel = 3;
        break;
      }
    case HAL_TIM_ACTIVE_CHANNEL_4: {
        channel = 4;
        break;
      }
    default:
      return;
  }


    HardwareTimer *HT= getTimerOOP(htim);
  if (HT->callbacksCaptureCompare[channel]) {
    HT->callbacksCaptureCompare[channel]();
  }
}

/**
  * @brief  Check whether HardwareTimer is running (paused or resumed).
  * @retval return true if the HardwareTimer is running
  */
bool HardwareTimer::isRunning()
{
  return LL_TIM_IsEnabledCounter(this->timer->Instance);
}

/**
  * @brief  Check whether channel is running (paused or resumed).
  * @param  channel: Arduino channel [1..4]
  * @retval return true if HardwareTimer is running and the channel is enabled
  */
bool HardwareTimer::isRunningChannel(uint32_t Channel) {


    int IT= getIT(Channel);

    // 检查定时器是否处于运行状态
    if (__HAL_TIM_GET_FLAG(this->timer, TIM_FLAG_UPDATE) != RESET) {
        // 检查相应通道的使能状态
        switch (Channel) {
            case 1:
                if (__HAL_TIM_GET_IT_SOURCE(this->timer, IT) != RESET) {
                    return true;
                }
                break;
            case 2:
                if (__HAL_TIM_GET_IT_SOURCE(this->timer, IT) != RESET) {
                    return true;
                }
                break;
            case 3:
                if (__HAL_TIM_GET_IT_SOURCE(this->timer, IT) != RESET) {
                    return true;
                }
                break;

            case 4:
                if (__HAL_TIM_GET_IT_SOURCE(this->timer, IT) != RESET) {
                    return true;
                }
                break;
                // 处理其他通道
            default:
                break;
        }
    }

    // 如果没有返回true，说明通道不是运行状态
    return false;
//  int LLChannel = getLLChannel(channel);
//  int interrupt = getIT(channel);
//  bool ret;
//
//  if (LLChannel == -1) {
//    Error_Handler();
//  }
//
//  if (interrupt == -1) {
//    Error_Handler();
//  }
//
//  // channel is running if: timer is running, and either output channel is
//  // enabled or interrupt is set
//  ret = LL_TIM_CC_IsEnabledChannel(this->timer->Instance, LLChannel)
//        || (__HAL_TIM_GET_IT_SOURCE(this->timer, (uint32_t)interrupt) == SET);
//  return (isRunning() && ret);
}

/**
  * @brief  Take into account registers update immediately if timer is not running,
  *         (independently from Preload setting)
  * @param  TIMx Timer instance
  * @retval None
  */
void HardwareTimer::updateRegistersIfNotRunning()
{
  if (!isRunning()) {
    if (LL_TIM_IsEnabledIT_UPDATE(timer->Instance)) {
      // prevent Interrupt generation from refresh()
      LL_TIM_DisableIT_UPDATE(timer->Instance);
      refresh();
      LL_TIM_ClearFlag_UPDATE(timer->Instance);
      LL_TIM_EnableIT_UPDATE(timer->Instance);
    } else {
      refresh();
    }
  }
}

/**
  * @brief  HardwareTimer destructor
  * @retval None
  */
HardwareTimer::~HardwareTimer()
{
  timer= nullptr;
    for (int i = 0; i < 1 + TIMER_CHANNELS; ++i) {
        callbacks[i]= nullptr;
        callbacksCaptureCompare[i]= nullptr;

    }
}



/**
  * @brief  This function return the timer clock frequency.
  * @param  None
  * @retval frequency in Hz
  */
uint32_t HardwareTimer::getTimerClkFreq()
{
    uint32_t apb1Freq, apb2Freq;

    // 根据定时器实例动态选择APB总线类型
    if (timer->Instance == TIM1 || timer->Instance == TIM8
//    || timer->Instance == TIM15 || htim->Instance == TIM16 || htim->Instance == TIM17
    ) {
        // 定时器位于APB2上
        apb2Freq = HAL_RCC_GetPCLK2Freq();
         apb2Freq /= (timer->Init.Prescaler + 1);

        return apb2Freq/(timer->Init.Period+1);
    } else {
        // 定时器位于APB1上
        apb1Freq = HAL_RCC_GetPCLK1Freq();
        apb1Freq /= (timer->Init.Prescaler + 1);
        return apb1Freq/(timer->Init.Period+1);
    }
}

/**
  * @brief  This function will reset the timer
  * @param  None
  * @retval None
  */
void HardwareTimer::timerHandleDeinit()
{
  HAL_TIM_Base_Stop_IT(timer);
  HAL_TIM_Base_DeInit(timer);
}


int HardwareTimer::getChannel(uint32_t channel)
{
    uint32_t return_value;

    switch (channel) {
        case 1:
            return_value = TIM_CHANNEL_1;
            break;
        case 2:
            return_value = TIM_CHANNEL_2;
            break;
        case 3:
            return_value = TIM_CHANNEL_3;
            break;
        case 4:
            return_value = TIM_CHANNEL_4;
            break;
        default:
            return_value = -1;
    }
    return return_value;
}

int HardwareTimer::getIT(uint32_t channel)
{
    uint32_t return_value;

    switch (channel) {
        case 1:
            return_value = TIM_IT_CC1;
            break;
        case 2:
            return_value = TIM_IT_CC2;
            break;
        case 3:
            return_value = TIM_IT_CC3;
            break;
        case 4:
            return_value = TIM_IT_CC4;
            break;
        default:
            return_value = -1;
    }
    return return_value;
}

#ifdef HAVE_TIMER1
HardwareTimer TIMER1(&htim1);
#endif
#ifdef HAVE_TIMER2
HardwareTimer TIMER2(&htim2);
#endif
#ifdef HAVE_TIMER3
HardwareTimer TIMER3(&htim3);
#endif
#ifdef HAVE_TIMER4
HardwareTimer TIMER4(&htim4);
#endif
#ifdef HAVE_TIMER5
HardwareTimer TIMER5(&htim5);
#endif
#ifdef HAVE_TIMER6
HardwareTimer TIMER6(&htim6);
#endif
#ifdef HAVE_TIMER7
HardwareTimer TIMER7(&htim7);
#endif
#ifdef HAVE_TIMER8
HardwareTimer TIMER8(&htim8);
#endif
#ifdef HAVE_TIMER9
HardwareTimer TIMER9(&htim9);
#endif
#ifdef HAVE_TIMER10
HardwareTimer TIMER10(&htim10);
#endif
#ifdef HAVE_TIMER11
HardwareTimer TIMER11(&htim11);
#endif
#ifdef HAVE_TIMER12
HardwareTimer TIMER12(&htim12);
#endif
#ifdef HAVE_TIMER13
HardwareTimer TIMER13(&htim13);
#endif
#ifdef HAVE_TIMER14
HardwareTimer TIMER14(&htim14);
#endif

/******************************************************************************/
/*                            TIMx IRQ HANDLER                                */
/******************************************************************************/
extern "C" {

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    HardwareTimer::captureCompareCallback(htim);
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim) {
    HardwareTimer::captureCompareCallback(htim);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    HardwareTimer::updateCallback(htim);
}

}
#endif // HAL_TIM_MODULE_ENABLED && !HAL_TIM_MODULE_ONLY
