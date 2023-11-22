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
//BaseGPIO led(F9, GpioMode::output_pp);
BaseGPIO led1(F10,GpioMode::output_pp);
void keycall(){

//    led.toggle();
}
void timecall(){
//    led.toggle();
}
void time12(){
    Baseserial<<"time12"<<endl;
//    led.toggle();
}
//BaseTime time(TIMER_6);
BasePWMTimer timer1(TIMER_14,F9,GPIO_AF9_TIM14);
void  MyMian(){
    uint16_t ledrpwmval = 0;
    uint8_t dir = 1;
    Baseserial.begin(115200);
    Baseserial<<"hello"<<endl;
//    time.once(5.0,time12);
    timer1.startPWM_ms(500, 84, TIM_CHANNEL_1, 0.5);

    for (;;){
//        HAL_Delay(10);
//        if (dir)ledrpwmval++;                   /* dir==1 ledrpwmval递增 */
//        else ledrpwmval--;                      /* dir==0 ledrpwmval递减 */
//
//        if (ledrpwmval > 300)dir = 0;           /* ledrpwmval到达300后，方向为递减 */
//        if (ledrpwmval == 0)dir = 1;            /* ledrpwmval递减到0后，方向改为递增 */
//        timer1.setPWMDutyCycle(ledrpwmval);
//        while (Baseserial.available()){
//            Baseserial.write(Baseserial.read());
//        }
    }
}