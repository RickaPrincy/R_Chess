#include "header/f_prototypes.hpp"

static Piece *pieceSelected = NULL;

Piece *getPieceSelected(){
    return pieceSelected;
}

void initPieceSelected(){
    pieceSelected->isSelected = false;
    pieceSelected = NULL;
}

void changePosition(int x, int y){
    pieceSelected->x = x;
    pieceSelected->y = y;
    return;
}



