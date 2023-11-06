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
void keycall(){
    GPIO led(F9,GpioMode::output_pp);
    led.write(0);
}
void  MyMian(){
    GPIO Led(F10,GpioMode::output_pp);
    GPIO key(E4,GpioMode::input);
    key.attachInterrupt(keycall,GpioExit::it_falling);
    for (;;){
        Led.toggle();
        HAL_Delay(1000);
    }
}