#include "header/f_prototypes.hpp"

void calcul(){
    Piece *piece = getPieceSelected();
    int increment = piece->color == WHITE ? -1 : 1;
    int y = piece->y + increment;

    if(piece->type == PAWN){
        if(y >= 0 && y < 8 && getCase(piece->x,y)->isEmpty()){
            getCase(piece->x,y)->isValid = true;
        }
    }
}