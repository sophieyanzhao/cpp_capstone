#include "controller.h"
#include <iostream>
#include "SDL.h"
#include <thread>


void Controller::HandleInput(std::shared_ptr<MutexVariable<bool>> running) {
  SDL_Event e;
  //TODO: potential data race
  while (SDL_PollEvent(&e) && (running->get())){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    if (e.type == SDL_QUIT) {
      running->set(false);
      std::string m = running->get() ? "true" : "false";
      SDL_Log("current state");
      SDL_Log(m.c_str());
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_ESCAPE:
            running->set(false);
            break;
      }
    }
  }
}