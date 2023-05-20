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
    getCase(pieceSelected->x, pieceSelected->y)->piece = NULL;
    pieceSelected->x = x;
    pieceSelected->y = y;
    getCase(x,y)->piece = pieceSelected;
    initPieceSelected();
    return;
}

void makeSelected(Piece *piece){
    piece->isSelected = true;
    pieceSelected = piece;
}

void capture(Piece *piece, int x, int y){
    if(!piece->isSelected)
        piece->isOnBoard = false;
    
    changePosition(x,y);
}
