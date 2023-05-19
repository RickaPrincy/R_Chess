#include "header/f_prototypes.hpp"

void load(){
    loadBackground();
    loadPieces();
}

void init(){
    initPieces();
}

void draw(){
    drawBackground();
    drawPieces();

    SDL_RenderPresent(getRenderer());
    
    SDL_Delay(1);
}

void cleanEverything(){
    cleanPieces();
    cleanBackground();
    cleanFirstInit();
}