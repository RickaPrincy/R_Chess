#include "header/f_prototypes.hpp"

void calcul(){
    Piece *piece = getPieceSelected();
    int increment = piece->color == WHITE ? -1 : 1;
    int y = piece->y + increment;

    if(piece->type == PAWN){

        /* ----------------------------------------------------- */
        if(y >= 0 && y < 8 && getCase(piece->x,y)->isEmpty()){
            getCase(piece->x,y)->isValid = true;
        }
        /* ----------------------------------------------------- */
        if(
            ((piece->y == 1 && piece->color == BLACK) || (piece->y == 6 && piece->color == WHITE))
            && getCase(piece->x,y)->isEmpty() && getCase(piece->x,y + increment)->isEmpty()
        ){
            getCase(piece->x,y + increment)->isValid = true;
        }
        /* ----------------------------------------------------- */
        if( piece->x < 7 && !getCase(piece->x + 1,y)->isEmpty() && getCase(piece->x + 1,y)->piece->color != piece->color ){
            getCase(piece->x + 1,y)->isValid = true;
        }
        /* ----------------------------------------------------- */
        if(piece->x > 0 && !getCase(piece->x - 1,y)->isEmpty() && getCase(piece->x - 1,y)->piece->color != piece->color){
            getCase(piece->x - 1,y)->isValid = true;
        }
    }
}