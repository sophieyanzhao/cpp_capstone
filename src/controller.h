#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>

class Controller {
 public:
    void HandleInput(std::shared_ptr<bool> running);
};

#endif