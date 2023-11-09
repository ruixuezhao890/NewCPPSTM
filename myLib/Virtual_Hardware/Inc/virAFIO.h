/**
*********************************************************************
*********
* @project_name :car0
* @file : virAFIO.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6 
*********************************************************************
*********
*/
//

#ifndef CAR0_VIRAFIO_H
#define CAR0_VIRAFIO_H
#include "Resources.h"
//hal库中将afio与引脚输入输出的模式算在了一起所有该类被闲置
#if 0
class virAFIO {
public:
   virtual void afio_init(Pin_enum pin, AFIO_mode mode)=0;
};

#endif
#endif //CAR0_VIRAFIO_H
