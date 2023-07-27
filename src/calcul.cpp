#include "header/f_prototypes.hpp"

//test if there is a check
int isThereACheck(){
    Piece *kingBlack = getPiece(4), *kingWhite = getPiece(28);

    if(*getTurn() == BLACK)
        return getCase(kingBlack->x,kingBlack->y)->attackerWhite.size();
    else
        return getCase(kingWhite->x,kingWhite->y)->attackerBlack.size();
}

//test if one case is a case valid for a selected piece
bool testCase(Piece *piece,int x, int y,short forWhat){
    if(forWhat == CASE_VALID || forWhat == CHECK_MATE){
        if((getCase(x,y)->isEmpty() || getCase(x,y)->piece->color != piece->color) && !isCheckAfterMove(piece,x,y))
            if(forWhat == CHECK_MATE)
                *getCheckMatePossible() = false;
            else
                getCase(x,y)->isValid = true;
    }
    else if(piece->color == WHITE)
        getCase(x,y)->attackerWhite.push_back(piece);
    else
        getCase(x,y)->attackerBlack.push_back(piece);

    return getCase(x,y)->isEmpty();
}

//calcul all case attacked
void globalCalcul(bool shouldInitCaseValid){
    
    if(shouldInitCaseValid)
        initCases(LIST_AND_VALID);
    else
        initCases(LIST_OF_ATTACKER);    
    
    //calcul case attacked
    for(int i = 0; i < 32; i++){
        if(getPiece(i)->type == KING){
            calculKing(getPiece(i),ATTACKER);
        }
        else if(getPiece(i)->isOnBoard){
            calcul(getPiece(i),ATTACKER);
        }
    }
}

//calcul case valid || case attacked for a given piece
void calcul(Piece *piece, short forWhat){
    int xx, yy;

    //cause in chess when there is a double check (or more), the king is forced to move
    if(isThereACheck() >= 2)
        return;

    if(piece->type == PAWN){
        int increment = piece->color == WHITE ? -1 : 1;
        int y = piece->y + increment;
        
        if(forWhat != ATTACKER){
            if(y >= 0 && y < 8 && getCase(piece->x,y)->isEmpty())
                testCase(piece,piece->x,y,forWhat);

            /* ----------------------------------------------------- */
            if(
                ((piece->y == 1 && piece->color == BLACK) || (piece->y == 6 && piece->color == WHITE))
                && getCase(piece->x,y)->isValid && getCase(piece->x,y + increment)->isEmpty()
            ){
                testCase(piece,piece->x,y + increment,forWhat);
            }
        }
        /* ----------------------------------------------------- */
        if(piece->x < 7 && !getCase(piece->x + 1,y)->isEmpty()){
            testCase(piece,piece->x + 1,y,forWhat);
        }
        /* ----------------------------------------------------- */
        if(piece->x > 0 && !getCase(piece->x - 1,y)->isEmpty()){
            testCase(piece,piece->x - 1,y,forWhat);
        }
    }
    else if(piece->type == KNIGHT){
        if(piece->y < 6){
            if(piece->x < 7)
                testCase(piece,piece->x + 1, piece->y + 2,forWhat);
            if(piece->x > 0)
                testCase(piece,piece->x - 1, piece->y + 2,forWhat);
        }

        /*---------------------------------------------------*/
        if(piece->y > 1){
            if(piece->x < 7)
                testCase(piece,piece->x + 1, piece->y - 2,forWhat);
            if(piece->x > 0)
                testCase(piece,piece->x - 1, piece->y - 2,forWhat);
        }

        /*---------------------------------------------------*/
        if(piece->x < 6){
            if(piece->y < 7)
                testCase(piece,piece->x + 2, piece->y + 1,forWhat);
            if(piece->y > 0)
                testCase(piece,piece->x + 2, piece->y - 1,forWhat);
        }

        /*---------------------------------------------------*/
        if(piece->x > 1){
            if(piece->y < 7)
                testCase(piece,piece->x - 2, piece->y + 1,forWhat);
            if(piece->y > 0)
                testCase(piece,piece->x - 2, piece->y - 1,forWhat);
        }
    }
    else{
        if(piece->type == QUEEN || piece->type == BISHOP){
            xx = piece->x,yy = piece->y;
            while(true){
                if(xx == 7 || yy == 7 || !testCase(piece,++xx,++yy,forWhat))
                    break;
            }
                
            /* ----------------------------------------------- */
            xx = piece->x,yy = piece->y;
            while(true){
                if(xx == 0 || yy == 0 || !testCase(piece,--xx,--yy,forWhat))
                    break;
            }

            /* ----------------------------------------------- */
            xx = piece->x,yy = piece->y;
            while(true){
                if(xx == 0 || yy == 7 || !testCase(piece,--xx,++yy,forWhat))
                    break;
            }

            /* ----------------------------------------------- */
            xx = piece->x,yy = piece->y;
            while(true){
                if(xx == 7 || yy == 0 || !testCase(piece,++xx,--yy,forWhat))
                    break;
            }
        }
        if(piece->type == QUEEN || piece->type == ROOK){
            xx = piece->x,yy = piece->y;
            while(true){
                if(yy == 7 || !testCase(piece,xx,++yy,forWhat))
                    break;
            }
                
            /* ----------------------------------------------- */
            xx = piece->x,yy = piece->y;
            while(true){
                if(yy == 0 || !testCase(piece,xx,--yy,forWhat))
                    break;
            }

            /* ----------------------------------------------- */
            xx = piece->x,yy = piece->y;
            while(true){
                if(xx == 7 || !testCase(piece,++xx,yy,forWhat))
                    break;
            }
                
            /* ----------------------------------------------- */
            xx = piece->x,yy = piece->y;
            while(true){
                if(xx == 0 || !testCase(piece,--xx,yy,forWhat))
                    break;
            }
        }
    }
}