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
    getInput()->isOnMove = false;
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

void drawPieceSelected(){
	if(pieceSelected != NULL){
        SDL_Rect dest,src;

        dest.w = dest.h = src.w = src.h = PIECE_SIZE;
        dest.x = getImagePosition(pieceSelected->type);
        dest.y = pieceSelected->color == WHITE ? 0 : 50;

        src.x = getInput()->mouseX - 25;
        src.y = getInput()->mouseY - 25;

        SDL_RenderCopy(getRenderer(),getPiecesImage(),&dest,&src);
	}
}
