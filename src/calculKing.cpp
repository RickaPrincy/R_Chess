#include "header/f_prototypes.hpp"

void testCaseForKing(Piece *piece,short forWhat,int x,int y){
    if(forWhat == ATTACKER){
        if(piece->color == WHITE)
            getCase(x,y)->attackerWhite.push_back(piece);
        else
            getCase(x,y)->attackerBlack.push_back(piece);
    }
    else if(
        (getCase(x,y)->isEmpty() || getCase(x,y)->piece->color != piece->color)
        &&
        (
            ( getCase(x,y)->attackerBlack.size() == 0 && piece->color == WHITE) ||
            ( getCase(x,y)->attackerWhite.size() == 0 && piece->color == BLACK)
        ) 
    ){
        if(isThereACheck() == 0 || !isCheckAfterMove(piece, x, y)){
            if(forWhat == CASE_VALID)
                getCase(x,y)->isValid = true;
            else
                *getCheckMatePossible() = false;
        }
    }
}

void calculKing(Piece *piece, short forWhat){
    int x = piece->x, y = piece->y;

    if(x > 0){
        testCaseForKing(piece,forWhat,x - 1 , y);
        if(y < 7)
            testCaseForKing(piece,forWhat,x - 1, y + 1);
        if(y > 0)
            testCaseForKing(piece,forWhat,x - 1, y - 1);
    }
    
    if(x < 7){
        testCaseForKing(piece,forWhat,x + 1 , y);
        if(y < 7)
            testCaseForKing(piece,forWhat,x + 1, y + 1);
        if(y > 0)
            testCaseForKing(piece,forWhat,x + 1, y - 1);
    }

    if(y < 7)
        testCaseForKing(piece,forWhat,x, y + 1);
    if(y > 0)
        testCaseForKing(piece,forWhat,x,y - 1);
    
    //handler castle
    if(forWhat && x == 4 && !piece->alreadyMove && isThereACheck() == 0){
        
        //on the king's side
        if(
            getCase(5,y)->isEmpty()
            && (
                ( getCase(5,y)->attackerBlack.size() == 0 && piece->color == WHITE ) ||
                ( getCase(5,y)->attackerWhite.size() == 0 &&piece->color == BLACK ) 
            )
            && getCase(6,y)->isEmpty()
            && (
                ( getCase(6,y)->attackerBlack.size() == 0 && piece->color == WHITE ) ||
                ( getCase(6,y)->attackerWhite.size() == 0 &&piece->color == BLACK ) 
            )
        ){
            if( !getCase(7,y)->isEmpty() && !getCase(7,y)->piece->alreadyMove){
                getCase(6,y)->isValid = true;
            }
        }
        
        //on the queen's side
        if(
            getCase(3,y)->isEmpty()
            && (
                ( getCase(3,y)->attackerBlack.size() == 0 && piece->color == WHITE ) ||
                ( getCase(3,y)->attackerWhite.size() == 0 &&piece->color == BLACK ) 
            )
            && getCase(2,y)->isEmpty()
            && (
                ( getCase(2,y)->attackerBlack.size() == 0 && piece->color == WHITE ) ||
                ( getCase(2,y)->attackerWhite.size() == 0 &&piece->color == BLACK ) 
            )
        ){
            if( !getCase(0,y)->isEmpty() && !getCase(0,y)->piece->alreadyMove){
                getCase(2,y)->isValid = true;
            }
        }
    }
}