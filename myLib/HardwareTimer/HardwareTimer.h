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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HARDWARETIMER_H_
#define HARDWARETIMER_H_

/* Includes ------------------------------------------------------------------*/
//#include "timer.h"
//#include "stm32yyxx_ll_tim.h"
#include "stm32f4xx.h"
#ifdef  HAL_TIM_MODULE_ENABLED

#define  TIMER_CHANNELS 4    // channel5 and channel 6 are not considered here has they don't have gpio output and they don't have interrupt

#ifdef __cplusplus

#include <functional>
using callback_function_t = std::function<void(void)>;

/* Class --------------------------------------------------------*/
class HardwareTimer {
public:
    HardwareTimer();
    HardwareTimer(TIM_HandleTypeDef *instance);
    ~HardwareTimer();  // Destructor
    void setup(TIM_HandleTypeDef *instance);
    void pause(void);
    void pauseCapture(uint32_t Channel);
    void pauseOutputCompare(uint32_t Channel);
    void resume(void);
    void resumeCapture(uint32_t Channel);
    void resumeOutputCompare(uint32_t Channel);
    //普通的中断函数
    void attachInterrupt(callback_function_t callback);
    void detachInterrupt();
    bool hasInterrupt();

    //capture中断函数
    void attachInterrupt(uint32_t channel, callback_function_t callback);
    void detachInterrupt(uint32_t channel);
    bool hasInterrupt(uint32_t channel);

    void timerHandleDeinit();
    void refresh(void);

    uint32_t getTimerClkFreq();

    static void captureCompareCallback(TIM_HandleTypeDef *htim);
    static void updateCallback(TIM_HandleTypeDef *htim);

    void updateRegistersIfNotRunning();

    bool isRunning();
    bool isRunningChannel(uint32_t);

    TIM_HandleTypeDef *getHandle();
private:
    int getChannel(uint32_t channel);
    int getIT(uint32_t channel);
    TIM_HandleTypeDef *timer;
    callback_function_t callbacks[1 + TIMER_CHANNELS];
    callback_function_t callbacksCaptureCompare[1 + TIMER_CHANNELS];
};



extern HardwareTimer TIMER1;
extern HardwareTimer TIMER2;
extern HardwareTimer TIMER3;
extern HardwareTimer TIMER4;
extern HardwareTimer TIMER5;
extern HardwareTimer TIMER6;
extern HardwareTimer TIMER7;
extern HardwareTimer TIMER8;
extern HardwareTimer TIMER9;
extern HardwareTimer TIMER10;
extern HardwareTimer TIMER11;
extern HardwareTimer TIMER12;
extern HardwareTimer TIMER13;
extern HardwareTimer TIMER14;

#endif /* __cplusplus */

#endif  // HAL_TIM_MODULE_ENABLED && !HAL_TIM_MODULE_ONLY
#endif  // HARDWARETIMER_H_
