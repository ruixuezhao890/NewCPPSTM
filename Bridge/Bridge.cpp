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

    led.toggle();
}
void  MyMian(){

    Baseserial.begin(115200);
    Baseserial.println("hello world");
    Baseserial<<"hloo world"<<endl;
    Baseserial.print(3.1415926,6);Baseserial.println();
    BaseGPIO Led(F10, GpioMode::output_pp);
    BaseGPIO key(E4, GpioMode::input);
    BaseGPIO Key0(A0,GpioMode::input);
    key.attachInterrupt(keycall,GpioExit::it_falling,2,2);
    Key0.attachInterrupt(keycall,GpioExit::it_rising,3,2);
    for (;;){
        Led.toggle();
        HAL_Delay(1000);
        while (Baseserial.available()){
            Baseserial.write(Baseserial.read());
        }
    }
}