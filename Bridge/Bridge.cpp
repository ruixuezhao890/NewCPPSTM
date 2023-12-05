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
void  MyMian(){

    Serial0.uart_init();
    Serial0.print("hello world");
    uint16_t  flag=0;
    for (;;){
//        if (Serial0.available()){
//            Serial0.println(Serial0.read());
//        }
           auto ret=Serial0.readString();
           Serial0.println(ret);




    }
}