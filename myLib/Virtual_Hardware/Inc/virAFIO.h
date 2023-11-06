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
class virAFIO {
public:
   virtual void afio_init(Pin_enum pin, AFIO_mode mode)=0;
};


#endif //CAR0_VIRAFIO_H
