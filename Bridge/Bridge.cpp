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
//    Baseserial<<"time12"<<endl;
    led1.toggle();
}
BaseTime time(TIMER_6);
BasePWMTimer PWMtimer(TIMER_14,F9,GPIO_AF9_TIM14,1,2);
BaseADC ADC0(ADC_1);
Pin_enum adcPin=A4;
ADC_CH  adcch=ADC_CH4;
void  MyMian(){
    uint16_t ledrpwmval = 0;
    uint8_t dir = 1;
    ADC0.begin(&adcPin);
    ADC0.BaseADCChannelSet(&adcch);
    Baseserial.beginDMA(115200);
    Baseserial<<endl;
    Baseserial<<"hello"<<endl;
    Baseserial<<12;
    Baseserial<<"\n";

   time.attach(5.0,time12);
   PWMtimer.startPWM_ms(500-1,84-1,TIM_CHANNEL_1,0.5);

    for (;;){
        int temp=ADC0.BaseADCGetValue(); HAL_Delay(1000);
        Baseserial<<temp;
//        Baseserial<<endl;
//        while (Baseserial.available()){
//            Baseserial.write(Baseserial.read());
//        }

//        if (dir)ledrpwmval++;                   /* dir==1 ledrpwmval递增 */
//        else ledrpwmval--;                      /* dir==0 ledrpwmval递减 */
//
//        if (ledrpwmval > 300)dir = 0;           /* ledrpwmval到达300后，方向为递减 */
//        if (ledrpwmval == 0)dir = 1;            /* ledrpwmval递减到0后，方向改为递增 */
//        PWMtimer.setPWMDutyCycle(ledrpwmval);

    }
}