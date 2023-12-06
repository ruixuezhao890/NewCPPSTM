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
void LEd(){
    gpio_toggle(F9);
    Serial0.println("run");
}
void  MyMian(){

    Serial0.uart_DMAInit();
    HAL_Delay(100);
    Serial0.println("hello world");

    Serial0.println();
    TIMER6.attachInterrupt(LEd);
    TIMER6.resume();
    uint16_t  flag=0;
    for (;;){
           auto ret=Serial0.readString();
           Serial0.println(ret);




    }
}