#include "header/f_prototypes.hpp"

void load(){
    loadBackground();
    loadPieces();
}

void init(){
    initCases(PIECE);
    initPieces();
    *getTurn() = WHITE;
}

void draw(){
    drawBackground();
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