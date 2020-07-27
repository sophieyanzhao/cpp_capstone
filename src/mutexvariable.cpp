#include "mutexvariable.h"

template <class T>
T MutexVariable<T>::get(){
            std::unique_lock lck(_mutex);
            return _var;
}

template <class T>
void MutexVariable<T>::set(T input){
            std::unique_lock lck(_mutex);
            _var=input;
        }

void Score::AddOne(){
            _var=_var+1;
        }

template <class T>
T MessageQueue<T>::receive(){
    std::unique_lock<std::mutex> uLock(_mutex);
    _cond.wait(uLock, [this] { return !_messages.empty(); }); // prevent spurious wakeup using condition variable
    T msg = std::move(_messages.back());
    _messages.pop_back();
    return msg; // will not be copied due to return value optimization (RVO) in C++
    }


template <class T>
void MessageQueue<T>::send(T msg){
    std::lock_guard<std::mutex> uLock(_mutex);
    _messages.push_back(std::move(msg));
    _cond.notify_one(); 
}

Position::Position(int x, int y):_x(x), _y(y) {};

template class MutexVariable<int>;
template class MutexVariable<bool>;
template class MessageQueue<Position>;
