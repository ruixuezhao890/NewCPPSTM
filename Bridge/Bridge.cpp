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
//    Baseserial<<"hello world"<<endl;
//    Baseserial.print(3.1415926,6);Baseserial.println();
//    Baseserial.print(21,HEX);
//    BaseGPIO Led(F10, GpioMode::output_pp);
//    BaseGPIO key(E4, GpioMode::input);
//    BaseGPIO Key0(A0,GpioMode::input);
//    key.BaseSetCallBack(keycall,GpioExit::it_falling,2,2);
//    Key0.BaseSetCallBack(keycall,GpioExit::it_rising,3,2);
//
//    BaseTime baseTime(TIMER_8);
//    baseTime.beginBaseTime(8400,1000);
//    baseTime.TimeSetCallBack(timecall);
//    BaseTime baseTime12(TIMER_12);
//    baseTime12.beginBaseTime(8400,1000);
  //  baseTime12.TimeSetCallBack(time12);
uint8_t dir=1;
uint16_t ledpemval0;
  GenericTIMMode genericTimMode={GenericMode::TIME_PWM,F9,GPIO_AF9_TIM14,TIM_CHANNEL_1};
  BaseTime baseTime(TIMER_14);
  baseTime.beginGenericTime(500-1,84-1,genericTimMode);
    for (;;){
        HAL_Delay(10);
        if (dir)ledpemval0++;
        else ledpemval0--;
        if (ledpemval0>300)dir=0;
        else if (ledpemval0==0)dir=1;
        baseTime.TimePWMSetDutyCycle(ledpemval0);
//        while (Baseserial.available()){
//            Baseserial.write(Baseserial.read());
//        }
    }
}