/**
*********************************************************************
*********
* @project_name :New32
* @file : cmathpp.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/12/4 
*********************************************************************
*********
*/
//

#include <cassert>
#include "cmathpp.h"
template<typename _Tp>
_GLIBCXX14_CONSTEXPR
inline const _Tp&
min(const _Tp& __a, const _Tp& __b)
{
//    // concept requirements
//    __glibcxx_function_requires(_LessThanComparableConcept<_Tp>)
    //return __b < __a ? __b : __a;
    if (__b < __a)
        return __b;
    return __a;
}
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}