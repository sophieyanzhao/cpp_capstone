#include "controller.h"
#include <iostream>
#include "SDL.h"
#include <thread>
#include <future>
#include "mutexvariable.h"
using std::future;


void Controller::HandleInput(std::shared_ptr<MutexVariable<bool>> running,
std::shared_ptr<MutexVariable<bool>> exited, 
std::vector<std::shared_ptr<Mole>> &moles,std::shared_ptr<Score> score,
std::shared_ptr<bool> reset) {
  SDL_Event e;
  //TODO: potential data race
  while (SDL_PollEvent(&e) && exited->get()){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    if (e.type == SDL_QUIT) {
      running->set(false);
      exited->set(false);
      std::string m = running->get() ? "true" : "false";
      SDL_Log("current state");
      SDL_Log(m.c_str());
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
      std::string position = "x:" + std::to_string(x)+ "y:"+ std::to_string(y);
      SDL_Log(position.c_str());
      Position p=Position(x,y);
      std::vector<future<void>> tasks;
      for (std::shared_ptr<Mole> mole:moles){
        if (mole->alive->get()){
          tasks.emplace_back(std::async(std::launch::async, &MessageQueue<Position>::send, mole->hit_signals,p));
          }
        }
      SDL_Log("waiting for message to be sent");
      std::for_each(tasks.begin(),tasks.end(),[](std::future<void> &f){f.wait();});
      SDL_Log("All messages are sent");
    }
  }
}


