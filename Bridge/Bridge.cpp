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
BaseGPIO led1(F10,GpioMode::output_pp);
void keycall(){

//    led.toggle();
}
void timecall(){
    led.toggle();
}
void time12(){
    Baseserial<<"time12"<<endl;
    led.toggle();
}
BaseTime time(TIMER_6);
void  MyMian(){

    Baseserial.begin(115200);
    Baseserial<<"hello"<<endl;
    time.attach(8.0,time12);

    for (;;){
        while (Baseserial.available()){
            Baseserial.write(Baseserial.read());
        }
    }
}