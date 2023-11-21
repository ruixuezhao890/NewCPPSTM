/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseTime.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/11 
*********************************************************************
*********
*/
//

#ifndef CAR0_BASETIME_H
#define CAR0_BASETIME_H
// BaseTime.h


#include "virTime.h"

class BaseTime
{
public:
    // 构造函数
    BaseTime();
    BaseTime(Timer_enum timerEnum);
    // 析构函数
    ~BaseTime();
    static virTime* BasevirTime;
    // 回调函数类型，无参数


    // 将回调函数以秒为单位周期性地注册
    void attach(float seconds, callback_t callback);

    // 将回调函数以毫秒为单位周期性地注册
    void attach_ms(uint32_t milliseconds, callback_t callback);

    // 将带有特定参数的回调函数以秒为单位周期性地注册
    template<typename TArg>
    void attach(float seconds, void (*callback)(TArg), TArg arg);

    // 将带有特定参数的回调函数以毫秒为单位周期性地注册
    template<typename TArg>
    void attach_ms(uint32_t milliseconds, void (*callback)(TArg), TArg arg);

    // 将回调函数以秒为单位一次性地注册
    void once(float seconds, callback_t callback);

    // 将回调函数以毫秒为单位一次性地注册
    void once_ms(uint32_t milliseconds, callback_t callback);

    // 将带有特定参数的回调函数以秒为单位一次性地注册
    template<typename TArg>
    void once(float seconds, void (*callback)(TArg), TArg arg);

    // 将带有特定参数的回调函数以毫秒为单位一次性地注册
    template<typename TArg>
    void once_ms(uint32_t milliseconds, void (*callback)(TArg), TArg arg);

    // 取消注册当前已附加的回调函数
    void detach();

    // 检查当前是否有回调函数处于活动状态
    bool active();

protected:
    // 内部函数，用于将带有参数的回调函数附加到定时器
    void _attach_ms(uint32_t milliseconds, bool repeat, callback_with_arg_t callback, uint32_t arg);

protected:
    // 定时器的句柄
    Timer_enum _timer=Timer_enum::TIMER_END;

};




#endif //CAR0_BASETIME_H
