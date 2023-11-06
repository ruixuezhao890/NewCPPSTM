/**
*********************************************************************
*********
* @project_name :car0
* @file : Factory.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6 
*********************************************************************
*********
*/
//

#include "Factory.h"
MyGPIO *Factory::greatMyGPIO(){
    return  new MyGPIO();
}

MyAFIO *Factory::greatMyAFIO() {
    return new MyAFIO();
}
#if !Cubemx
MySystic *Factory::greatMySystic() {
    return new MySystic();
}
#endif