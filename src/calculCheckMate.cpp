#include "header/f_prototypes.hpp"

static bool isCheckMatePossible = false;

bool *getCheckMatePossible(){
    return &isCheckMatePossible;
}

void calculCheckMate(){
    if(isThereACheck() != 0){
        
        Piece *king = *getTurn() == WHITE ? getPiece(28) : getPiece(4); 

        makeSelected(king);
        calculKing(king, CHECK_MATE);
        initPieceSelected();
        
        if(isCheckMatePossible == false)
            return;

        if(isThereACheck() == 1){
            int i = king->color == WHITE ? 16 : 0;
            int stop = king->color == WHITE ? 32 : 16;

            for( int y = i; y < stop; y++){
                if(getPiece(y)->isOnBoard && getPiece(y)->type != KING){
                    makeSelected(getPiece(y));
                    calcul(getPiece(y),CHECK_MATE);
                    initPieceSelected();
                }

                if(isCheckMatePossible == false)
                    return;
            }
        }
    }
    else
        *getCheckMatePossible() = false;
}