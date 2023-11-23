/**
*********************************************************************
*********
* @project_name :car0
* @file : MyUniversalTimer.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/21 
*********************************************************************
*********
*/
//

#ifndef CAR0_MYUNIVERSALTIMER_H
#define CAR0_MYUNIVERSALTIMER_H
#include "MyBaseTime.h"
#include "MyGPIO.h"
class MyUniversalTimer: public MyBaseTime{
protected:
    uint32_t timerGreatPsc(Timer_enum timer, uint32_t arr, uint8_t PreemptPriority, uint8_t SubPriority) override;

    TIM_HandleTypeDef
    timerGreatPsc(Timer_enum timer, uint32_t psc, uint32_t arr, uint8_t PreemptPriority, uint8_t SubPriority) override;
protected:
    void timerPWMGreat(Timer_enum timer, uint8_t TIMExPWM_Channel, float dutyCycle);

    void timerPWMMultiplexPin(Pin_enum pin,uint8_t Alternate);
    // 启动周期性的PWM
    void startPWMPeriodic(Timer_enum timer, uint8_t TIMExPWM_Channel);

    // 停止PWM
    void stopPWM(Timer_enum timer,uint8_t TIMExPWM_Channel);

    void setPWMDutyCycle(uint32_t dutyCycle, Timer_enum timer, uint8_t TIMExPWM_Channel);
    // 删除定时器
    void deletePWMTimer(Timer_enum timer, uint8_t TIMExPWM_Channel);



    /*输入捕获相关代码*/
    void timerCaptureGreat(Timer_enum timer, uint32_t psc, uint32_t arr, uint8_t PreemptPriority, uint8_t SubPriority);
    void timerCaptureMultiplexPin(Pin_enum pin,uint8_t Alternate);
    // 启动周期性的Capture
    void startCapturePeriodic(Timer_enum timer, uint8_t TIMExPWM_Channel);

    // 停止Capture
    void stopCapture(Timer_enum timer,uint8_t TIMExPWM_Channel);
    //删除Capture
    void deleteCaptureTimer(Timer_enum timer, uint8_t TIMExPWM_Channel);

    virtual uint32_t getCaptureHighLevel();

private:
    uint32_t m_arr;
    MyGPIO UniversalAFIO;
};


#endif //CAR0_MYUNIVERSALTIMER_H
