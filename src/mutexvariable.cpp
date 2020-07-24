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

template class MutexVariable<int>;
template class MutexVariable<bool>;

