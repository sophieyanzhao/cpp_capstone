#include "controller.h"
#include <iostream>
#include "SDL.h"
#include <thread>
#include <future>
#include "mutexvariable.h"
#include <algorithm>
using std::future;


void Controller::HandleInput(std::shared_ptr<MutexVariable<bool>> running,
std::shared_ptr<MutexVariable<bool>> exited, 
std::vector<std::shared_ptr<Mole>> &moles,std::shared_ptr<Score> score,
std::shared_ptr<bool> reset) {
  SDL_Event e;
  while (SDL_PollEvent(&e) && exited->get()){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    if (e.type == SDL_QUIT) {
      running->set(false);
      exited->set(false);
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_ESCAPE:
            running->set(false);
            exited->set(false);
            break;
        case SDLK_r:
            if (!running->get()){ *reset=true;
                                  running->set(true);
                                  }
      }
    }else if (e.type==SDL_MOUSEBUTTONDOWN){
      int x, y;
      SDL_GetMouseState(&x,&y);
      Position p=Position(x,y);
      std::vector<future<void>> tasks;
      for (std::shared_ptr<Mole> mole:moles){
        // According to SDL documentation, it is recommended that the main thread always pulls user input
        // in order to speed up processing team, the main thread will send information to all moles which
        // will process concurrently 
        if (mole->alive->get()){
          tasks.emplace_back(std::async(std::launch::async, &MessageQueue<Position>::send, mole->hit_signals,p));
          }
        }
      std::for_each(tasks.begin(),tasks.end(),[](std::future<void> &f){f.wait();});
    }
  }
}


