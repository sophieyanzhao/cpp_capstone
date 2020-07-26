#ifndef MUTEXVARIABLE_H
#define MUTEXVARIABLE_H

#include <mutex>
#include <queue>

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


template <class T>
class MessageQueue{
    public:
        T receive();
        void send(T msg);

    private:
        std::mutex _mutex;
        std::condition_variable _cond;
        std::deque<T> _messages;
    };


struct Position{
    Position(int x, int y);
    int _x;
    int _y;
};

#endif