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