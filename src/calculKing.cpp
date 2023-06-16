#include "header/f_prototypes.hpp"

void testCaseForKing(Piece *piece,bool isForCaseValid,int x,int y){
    if(!isForCaseValid){
        if(piece->color == WHITE)
            getCase(x,y)->attackerWhite.push_back(piece);
        else
            getCase(x,y)->attackerBlack.push_back(piece);
    }
    else if(
        (
            getCase(x,y)->attackerBlack.size() == 0 
            &&piece->color == WHITE
            && (getCase(x,y)->isEmpty() || getCase(x,y)->piece->color != piece->color)
        ) ||
        (
            getCase(x,y)->attackerWhite.size() == 0 
            &&piece->color == BLACK
            && (getCase(x,y)->isEmpty() || getCase(x,y)->piece->color != piece->color)
        ) 
        
    ){
        getCase(x,y)->isValid = true;
    }
}

void calculKing(Piece *piece, bool isForCaseValid){
    int x = piece->x, y = piece->y;

    if(x > 0){
        testCaseForKing(piece,isForCaseValid,x - 1 , y);
        if(y < 7)
            testCaseForKing(piece,isForCaseValid,x - 1, y + 1);
        if(y > 0)
            testCaseForKing(piece,isForCaseValid,x - 1, y - 1);
    }
    
    if(x < 7){
        testCaseForKing(piece,isForCaseValid,x + 1 , y);
        if(y < 7)
            testCaseForKing(piece,isForCaseValid,x + 1, y + 1);
        if(y > 0)
            testCaseForKing(piece,isForCaseValid,x + 1, y - 1);
    }

    if(y < 7)
        testCaseForKing(piece,isForCaseValid,x, y + 1);
    if(y > 0)
        testCaseForKing(piece,isForCaseValid,x,y - 1);
}