#ifndef MUTEXVARIABLE_H
#define MUTEXVARIABLE_H

#include <mutex>
template <class T>
class MutexVariable {
    public:
        MutexVariable(T init):_var(init){};
        T get();
        void set(T input);

    private:
        T _var;
        std::mutex _mutex;


};
#endif