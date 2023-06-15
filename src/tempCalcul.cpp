#include "header/f_prototypes.hpp"

bool isCheckAfterMove(Piece *piece, int x,int y){
    Piece *capturedPiece = getCase(x,y)->piece;
    int oldX = piece->x, oldY = piece->y;
    bool result = false;

    if(capturedPiece == NULL){
        changePosition(x,y);
    }
    else{
        capture(x,y);
    }

    globalCalcul(false);

    if(isThereACheck() > 0){
        result = true;
    }

    piece->x = oldX;
    piece->y = oldY;
    getCase(oldX,oldY)->piece = piece;
    getCase(x,y)->piece = capturedPiece;

    if(capturedPiece != NULL){
        capturedPiece->isOnBoard = true;
    }

    globalCalcul(false);
    return result;

}