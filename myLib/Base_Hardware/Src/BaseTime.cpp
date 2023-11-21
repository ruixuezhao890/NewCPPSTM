/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseTime.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/11 
*********************************************************************
*********
*/
//

#include "BaseTime.h"
#include "MyBaseTime.h"
BaseTime::BaseTime() {

}

BaseTime::BaseTime(Timer_enum timerEnum, uint8_t PreemptPriority, uint8_t SubPriority) :
_timer(timerEnum),PreemptPriority(PreemptPriority),SubPriority(SubPriority){

}

BaseTime::~BaseTime() {

}

void BaseTime::attach(float seconds, callback_t callback) {
    _attach_ms(seconds * 1000, true, reinterpret_cast<callback_with_arg_t>(callback), 0);
}

void BaseTime::attach_ms(uint32_t milliseconds, callback_t callback) {
    _attach_ms(milliseconds, true, reinterpret_cast<callback_with_arg_t>(callback), 0);
}

template<typename TArg>
void BaseTime::attach(float seconds, void (*callback)(TArg), TArg arg) {
    static_assert(sizeof(TArg) <= sizeof(uint32_t), "attach() callback argument size must be <= 4 bytes");
    // C-cast serves two purposes:
    // static_cast for smaller integer types,
    // reinterpret_cast + const_cast for pointer types
    uint32_t arg32 = (uint32_t)arg;
    _attach_ms(seconds * 1000, true, reinterpret_cast<callback_with_arg_t>(callback), arg32);
}

template<typename TArg>
void BaseTime::attach_ms(uint32_t milliseconds, void (*callback)(TArg), TArg arg) {
    static_assert(sizeof(TArg) <= sizeof(uint32_t), "attach_ms() callback argument size must be <= 4 bytes");
    uint32_t arg32 = (uint32_t)arg;
    _attach_ms(milliseconds, true, reinterpret_cast<callback_with_arg_t>(callback), arg32);
}

void BaseTime::once(float seconds, callback_t callback) {
    _attach_ms(seconds * 1000, false, reinterpret_cast<callback_with_arg_t>(callback), 0);
}

void BaseTime::once_ms(uint32_t milliseconds, callback_t callback) {
    _attach_ms(milliseconds, false, reinterpret_cast<callback_with_arg_t>(callback), 0);
}

template<typename TArg>
void BaseTime::once(float seconds, void (*callback)(TArg), TArg arg) {
    static_assert(sizeof(TArg) <= sizeof(uint32_t), "attach() callback argument size must be <= 4 bytes");
    uint32_t arg32 = (uint32_t)(arg);
    _attach_ms(seconds * 1000, false, reinterpret_cast<callback_with_arg_t>(callback), arg32);
}

template<typename TArg>
void BaseTime::once_ms(uint32_t milliseconds, void (*callback)(TArg), TArg arg) {
    static_assert(sizeof(TArg) <= sizeof(uint32_t), "attach_ms() callback argument size must be <= 4 bytes");
    uint32_t arg32 = (uint32_t)(arg);
    _attach_ms(milliseconds, false, reinterpret_cast<callback_with_arg_t>(callback), arg32);
}

void BaseTime::detach() {
    if (_timer){
        timerStop(_timer);
        timerDelete(_timer);
        ExitValue.TimeExit[_timer]= nullptr;
    }
}

bool BaseTime::active() {
    return false;
}

void BaseTime::_attach_ms(uint32_t milliseconds, bool repeat, callback_with_arg_t callback, uint32_t arg) {
   if(_timer==Timer_enum::TIMER_END)return;
    ExitValue.arg[_timer]=reinterpret_cast<void*>(arg);
    ExitValue.TimeExit[_timer]=callback;
    if(_timer){
        timerStop(_timer);
        timerDelete(_timer);
    }
    timerGreatPsc(_timer, milliseconds, PreemptPriority, SubPriority);
    if (repeat){
       timerStartPeriodic(_timer);
    }else{
        timerStartOnce(_timer);
    }
}





