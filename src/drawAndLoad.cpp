#include "header/f_prototypes.hpp"

void load(){
    loadBackground();
}

void draw(){
    drawBackground();
    SDL_RenderPresent(getRenderer());
    SDL_Delay(1);
}

void cleanEverything(){
    cleanBackground();
    cleanFirstInit();
}