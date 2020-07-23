#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include "mutexvariable.h"

class Controller {
 public:
    void HandleInput(std::shared_ptr<MutexVariable<bool>> running);
};

#endif