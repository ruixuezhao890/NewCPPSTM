/**
*********************************************************************
*********
* @project_name :car0
* @file : Bridge.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/10/24 
*********************************************************************
*********
*/
//

#include "Bridge.h"
#include "User.h"
BaseGPIO led(F9, GpioMode::output_pp);
void keycall(){

//    led.toggle();
}
void timecall(){
    led.toggle();
}
void time12(){
    Baseserial<<"time12"<<endl;
}
void  MyMian(){

    Baseserial.begin(115200);
    Baseserial.println("hello world");

uint8_t dir=1;
uint16_t ledpemval0;
  GenericTIMMode genericTimMode={GenericMode::TIME_PWM,F9,Pin_null,GPIO_AF9_TIM14,TIM_CHANNEL_1};
  BaseTime baseTime(TIMER_14);
  baseTime.beginGenericTime(1000-1,84-1,genericTimMode);
  Baseserial<<(int)baseTime.TimePWM_getFrequency()<<endl;
  Baseserial<<(float)baseTime.TimePWM_getDutyCycle()<<endl;
    for (;;){
        HAL_Delay(10);
        if (dir)ledpemval0++;
        else ledpemval0--;
        if (ledpemval0>300)dir=0;
        else if (ledpemval0==0)dir=1;
        baseTime.TimePWM_setPulseWidth(ledpemval0);
//        while (Baseserial.available()){
//            Baseserial.write(Baseserial.read());
//        }
    }
}