#ifndef GRAPHICS_H
#define GRAPHICS_H

// #include "SDL.h" //  for vscode
#include <SDL2/SDL.h> // for ubuntu
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include "mutexvariable.h"
#include <memory>
#include <future>
#include <random>

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
    // this class is responsible for loading all images and freeing them after use 
    public:
        SDL_Surface* current_img;
        vector<SDL_Surface*> pictures;
        SDL_Surface* grass;
        vector<string> file_paths{"../images/1.png",//hidden
                            "../images/2.png", // start
                            "../images/3.png", //mid
                            "../images/4.png" //full
                            };
        Graphics();
        SDL_Surface* LoadSurface(std::string path);
        ~Graphics();

};

class Mole{
    // mole class does not own any graphical resources, it simply update stages 
    // renderer picks the right graphics from Graphics class according to a mole stage
    public:
        // variables 
        std::shared_ptr<MutexVariable<bool>> running;
        std::vector<MoleStage> transition {MoleStage::hidden, 
                                         MoleStage::start,
                                         MoleStage::mid,
                                         MoleStage::full,
                                         MoleStage::mid,
                                         MoleStage::start,
                                         MoleStage::hidden,
                                         MoleStage::hidden};
        SDL_Rect stretchRect;
        int idx{0};
        MoleStage stage{MoleStage::hidden};
        std::vector<float> offset = {0.0, 0.0, 25.0, 45.0};
        std::shared_ptr<MutexVariable<bool>> alive=std::make_shared<MutexVariable<bool>>(true);
        std::shared_ptr<MessageQueue<Position>> hit_signals=std::make_shared<MessageQueue<Position>>();
        std::thread moving_task,check_alive_task; // 2 threads, 1 for updating mole stages, 1 for checking if the mole
        // gets hit 
        // methods
        Mole(int x, int y, std::shared_ptr<MutexVariable<bool>> game_state);
        ~Mole();
        void Update();
        void CheckAlive(std::shared_ptr<Score> score, std::shared_ptr<MutexVariable<bool>> running);
        bool Hit(int &x,int &y);
        void Simulate(std::shared_ptr<Score> score);
    
    private: 
        Uint32 update_duration{50};
        Uint32 mole_start;
        Graphics *graphs;
        float ratio = 484.0/728.0;
        vector<SDL_Surface*> pictures;
        std::mutex _mutex;
    
};

#endif