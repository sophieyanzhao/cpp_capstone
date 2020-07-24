#include "controller.h"
#include <iostream>
#include "SDL.h"
#include <thread>


void Controller::HandleInput(std::shared_ptr<MutexVariable<bool>> running, std::shared_ptr<Mole> mole) {
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
    }else if (e.type==SDL_MOUSEBUTTONDOWN){
      int x, y;
      SDL_GetMouseState(&x,&y);
      // std::string position = "x:" + std::to_string(x)+ "y:"+ std::to_string(y);
      // SDL_Log(position.c_str());
      bool hitted=mole->Hit(x,y);
      
      std::string hitMessage="the mole gets hitted:"+std::to_string(hitted);
      SDL_Log(hitMessage.c_str());
    }
  }
}


