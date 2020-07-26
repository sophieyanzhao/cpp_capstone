#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include "mutexvariable.h"
#include "graphics.h"



class Controller{
    public: 
        void HandleInput(std::shared_ptr<MutexVariable<bool>> running, 
        std::shared_ptr<MutexVariable<bool>> exited,
        std::vector<std::shared_ptr<Mole>> &moles, std::shared_ptr<Score> score,
        std::shared_ptr<bool> reset);

};



#endif