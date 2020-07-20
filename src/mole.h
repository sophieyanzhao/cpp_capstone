#ifndef MOLE_H
#define MOLE_H

#include "SDL.h"
#include <vector>
#include <string>
#include <thread>


using std::vector;
using std::string;

enum MoleStage
{
    hidden,
    start,
    mid,
    full,
    sinking,
    end
};

class Graphics{
    public:
        Graphics();
        ~Graphics();
        SDL_Surface* LoadSurface( std::string path);
        SDL_Surface* current_img;
        SDL_Surface* front_surface;
        vector<SDL_Surface*> pictures;
        SDL_Surface* grass;
        vector<string> file_paths{"../images/1.png",
                            "../images/2.png",
                            "../images/3.png",
                            "../images/4.png",
                            "../images/3.png",
                            "../images/2.png",
                            "../images/1.png" };
};

class Mole{
    public:
    //constructor
        Mole(int x, int y);
        SDL_Rect stretchRect;
        ~Mole();
        void Update();
        // std::vector<std::thread> threads;
        //std::thread t;
        MoleStage stage{MoleStage::hidden};

    private: 
       
        Uint32 update_duration{200};
        Uint32 mole_start;
        Graphics *graphs;
        float ratio = 484.0/728.0;
        vector<SDL_Surface*> pictures;
    
};

#endif