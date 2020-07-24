#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL.h"
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include "mutexvariable.h"
#include <memory>

using std::vector;
using std::string;

enum MoleStage
{
    hidden,
    start,
    mid,
    full,
};

class Graphics{
    public:
        Graphics();
        ~Graphics();
        SDL_Surface* LoadSurface(std::string path);
        SDL_Surface* current_img;
        //SDL_PixelFormat* format;
        vector<SDL_Surface*> pictures;
        SDL_Surface* grass;
        vector<string> file_paths{"../images/1.png",//hidden
                            "../images/2.png", // start
                            "../images/3.png", //mid
                            "../images/4.png" //full
                            };

};

class Mole{
    public:
    //constructor
        Mole(int x, int y, std::shared_ptr<MutexVariable<bool>> game_state);
        SDL_Rect stretchRect;
        ~Mole();
        void Update();
        std::shared_ptr<MutexVariable<bool>> running;
        std::vector<MoleStage> transition {MoleStage::hidden, 
                                         MoleStage::start,
                                         MoleStage::mid,
                                         MoleStage::full,
                                         MoleStage::mid,
                                         MoleStage::start,
                                         MoleStage::hidden,
                                         MoleStage::hidden};
        int idx{0};
        MoleStage stage{MoleStage::hidden};
        std::vector<float> offset = {0.0, 0.0, 25.0, 45.0};
        //std::shared_ptr<MutexVariable<bool>> alive=std::make_shared<MutexVariable<bool>>(true);
        //bool CheckAlive(std::shared_ptr<MutexVariable<bool>> alive);
        bool Hit(int &x,int &y);
    
    private: 
        Uint32 update_duration{100};
        Uint32 mole_start;
        Graphics *graphs;
        float ratio = 484.0/728.0;
        vector<SDL_Surface*> pictures;
        bool GetGameState();
        std::mutex _mutex;
    
};

#endif