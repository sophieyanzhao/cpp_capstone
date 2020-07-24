#ifndef MUTEXVARIABLE_H
#define MUTEXVARIABLE_H

#include <mutex>
template <class T>
class MutexVariable {
    public:
        MutexVariable(T init):_var(init){};
        T get();
        void set(T input);

    protected:
        T _var;
        std::mutex _mutex;


};

class Score:public MutexVariable<int> {
    public:
        Score():MutexVariable<int>(0){};
        void AddOne();
};

#endif