/**
*********************************************************************
*********
* @project_name :car0
* @file : MyAFIO.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6 
*********************************************************************
*********
*/
//

#ifndef CAR0_MYAFIO_H
#define CAR0_MYAFIO_H
//hal库中将afio与引脚输入输出的模式算在了一起所有该类被闲置
#if 0
#include "virAFIO.h"
class MyAFIO: public virAFIO{
public:
    void afio_init(Pin_enum pin, AFIO_mode mode) override;
};
#endif

#endif //CAR0_MYAFIO_H
