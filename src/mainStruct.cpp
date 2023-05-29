#include "header/f_prototypes.hpp"

void load(){
    loadBackground();
    loadPieces();
}

void init(){
    initCases(false);
    initPieces();
}

void draw(){
    drawBackground();
    drawCasesSelected();
    drawCasesValid();
    drawPieces();
    drawPieceSelected();
    
    SDL_RenderPresent(getRenderer());
    
    SDL_Delay(1);
}

void cleanEverything(){
    cleanPieces();
    cleanBackground();
    cleanFirstInit();
}