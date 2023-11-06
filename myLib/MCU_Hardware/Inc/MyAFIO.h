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
#include "virAFIO.h"
class MyAFIO: public virAFIO{
public:
private:
    void afio_init(Pin_enum pin, AFIO_mode mode) override;
};


#endif //CAR0_MYAFIO_H
