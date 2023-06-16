#include "header/f_prototypes.hpp"

//test if there is a check
int isThereACheck(){
    Piece *kingBlack = getPiece(4), *kingWhite = getPiece(28);
    
    if(*getTurn() == BLACK){
        return getCase(kingBlack->x,kingBlack->y)->attackerWhite.size();
    }
    else{
        return getCase(kingWhite->x,kingWhite->y)->attackerBlack.size();
    }
}

//test if one case is a case valid for a selected piece
bool testCase(Piece *piece,int x, int y,bool isForCaseValid, Piece **hasfoundPiece,short typeOfPin){
    if(isForCaseValid){
        if(getCase(x,y)->isEmpty() || getCase(x,y)->piece->color != piece->color){
            int isCheck = isThereACheck();

            if(isCheck == 1){
                if(!isCheckAfterMove(piece,x,y)){
                    getCase(x,y)->isValid = true;
                }
            }
            else if(isCheck == 0){
                getCase(x,y)->isValid = true;
            }
        }
        return getCase(x,y)->isEmpty();
    }
    else if(*hasfoundPiece == NULL){
        if(piece->color == WHITE){
            getCase(x,y)->attackerWhite.push_back(piece);
        }
        else{
            getCase(x,y)->attackerBlack.push_back(piece);
        }
        if(!getCase(x,y)->isEmpty()){
            if(getCase(x,y)->piece->color == piece->color){
                return false;
            }

            *hasfoundPiece = getCase(x,y)->piece;    
        } 
        return true;
    }
    else if(getCase(x,y)->isEmpty()){
        return true;
    }
    else{
        if(getCase(x,y)->piece->color != piece->color && getCase(x,y)->piece->type == KING){
            switch(typeOfPin){
                case PINX:
                    (*hasfoundPiece)->isPinnedX = true;
                    break;
                case PINY:
                    (*hasfoundPiece)->isPinnedY = true;
                    break;
                case PINL:
                    (*hasfoundPiece)->isPinnedDiagonalLeft = true;
                    break;
                case PINR:
                    (*hasfoundPiece)->isPinnedDiagonalRight = true;
                    break;
                default: break;
            }
        }
        return false;
    }
}

//calcul all case attacked
void globalCalcul(bool shouldInitCaseValid){
    
    if(shouldInitCaseValid){
        initCases(LIST_AND_VALID);
    }
    else{
        initCases(LIST_OF_ATTACKER);    
    }
    
    //reset old pinned
    for(int i = 0; i < 32; i++){
        getPiece(i)->isPinnedX = getPiece(i)->isPinnedY = false;
        getPiece(i)->isPinnedDiagonalRight = getPiece(i)->isPinnedDiagonalLeft = false;
    }
    
    //calcul case attacked and current pinned
    for(int i = 0; i < 32; i++){
        if(getPiece(i)->type == KING){
            calculKing(getPiece(i),false);
        }
        else if(getPiece(i)->isOnBoard){
            calcul(getPiece(i),false);
        }
    }
}

//calcul case valid || case attacked for a given piece
void calcul(Piece *piece, bool isForCaseValid){
    int xx, yy;
    Piece *hasfoundPiece = NULL;

    if(piece->type == PAWN){

        int increment = piece->color == WHITE ? -1 : 1;
        int y = piece->y + increment;
        
        if(
            isForCaseValid && 
            !piece->isPinnedX && 
            !piece->isPinnedDiagonalLeft &&
            !piece->isPinnedDiagonalRight
        ){
            if(y >= 0 && y < 8 && getCase(piece->x,y)->isEmpty()){
                int isCheck = isThereACheck();

                if(isCheck == 1){
                    if(!isCheckAfterMove(piece,piece->x,y)){
                        getCase(piece->x,y)->isValid = true;
                    }
                }
                else if(isCheck == 0){
                    getCase(piece->x,y)->isValid = true;
                }
            }
            /* ----------------------------------------------------- */
            if(
                ((piece->y == 1 && piece->color == BLACK) || (piece->y == 6 && piece->color == WHITE))
                && getCase(piece->x,y)->isEmpty() && getCase(piece->x,y + increment)->isEmpty()
            ){
                int isCheck = isThereACheck();

                if(isCheck == 1){
                    if(!isCheckAfterMove(piece,piece->x,y)){
                        getCase(piece->x,y + increment)->isValid = true;
                    }
                }
                else if(isCheck == 0){
                    getCase(piece->x,y + increment)->isValid = true;
                }
            }
        }
        /* ----------------------------------------------------- */
        if(piece->x < 7 && !getCase(piece->x + 1,y)->isEmpty()){
            if(
                !isForCaseValid||
                (
                    !piece->isPinnedX && 
                    !piece->isPinnedY &&
                    (
                        (piece->color == WHITE && !piece->isPinnedDiagonalLeft) ||
                        (piece->color == BLACK && !piece->isPinnedDiagonalRight)
                    )
                )
            ){
                testCase(piece,piece->x + 1,y,isForCaseValid,&hasfoundPiece,NONE);
            }
        }
        /* ----------------------------------------------------- */
        if(piece->x > 0 && !getCase(piece->x - 1,y)->isEmpty()){
            if(
                !isForCaseValid||
                (
                    !piece->isPinnedX && 
                    !piece->isPinnedY &&
                    (
                        (piece->color == WHITE && !piece->isPinnedDiagonalRight) ||
                        (piece->color == BLACK && !piece->isPinnedDiagonalLeft)
                    )
                )
            ){
                testCase(piece,piece->x - 1,y,isForCaseValid,&hasfoundPiece,NONE);
            }
        }
    }
    else if(piece->type == KNIGHT){
		if(
            !isForCaseValid || 
            (
                !piece->isPinnedX && 
                !piece->isPinnedY &&
                !piece->isPinnedDiagonalRight &&
                !piece->isPinnedDiagonalLeft 
            )
        ){
            if(piece->y < 6){
                if(piece->x < 7)
                    testCase(piece,piece->x + 1, piece->y + 2,isForCaseValid,&hasfoundPiece,NONE);
                if(piece->x > 0)
                    testCase(piece,piece->x - 1, piece->y + 2,isForCaseValid,&hasfoundPiece,NONE);
            }

            /*---------------------------------------------------*/

            if(piece->y > 1){
                if(piece->x < 7)
                    testCase(piece,piece->x + 1, piece->y - 2,isForCaseValid,&hasfoundPiece,NONE);
                if(piece->x > 0)
                    testCase(piece,piece->x - 1, piece->y - 2,isForCaseValid,&hasfoundPiece,NONE);
            }

            /*---------------------------------------------------*/

            if(piece->x < 6){
                if(piece->y < 7)
                    testCase(piece,piece->x + 2, piece->y + 1,isForCaseValid,&hasfoundPiece,NONE);
                if(piece->y > 0)
                    testCase(piece,piece->x + 2, piece->y - 1,isForCaseValid,&hasfoundPiece,NONE);
            }

            /*---------------------------------------------------*/

            if(piece->x > 1){
                if(piece->y < 7)
                    testCase(piece,piece->x - 2, piece->y + 1,isForCaseValid,&hasfoundPiece,NONE);
                if(piece->y > 0)
                    testCase(piece,piece->x - 2, piece->y - 1,isForCaseValid,&hasfoundPiece,NONE);
            }
        }
    }
    else{
        if(piece->type == QUEEN || piece->type == BISHOP){
            if(
                !isForCaseValid || 
                (
                    !piece->isPinnedX && 
                    !piece->isPinnedY &&
                    !piece->isPinnedDiagonalRight
                )
            ){
                hasfoundPiece = NULL;
                xx = piece->x,yy = piece->y;
                while(true){
                    if(xx == 7 || yy == 7 || !testCase(piece,++xx,++yy,isForCaseValid,&hasfoundPiece,PINL))
                        break;
                }
                
                /* ----------------------------------------------- */
                hasfoundPiece = NULL;
                xx = piece->x,yy = piece->y;
                while(true){
                    if(xx == 0 || yy == 0 || !testCase(piece,--xx,--yy,isForCaseValid,&hasfoundPiece,PINL))
                        break;
                }
            }

            /* ----------------------------------------------- */
            if(
                !isForCaseValid || 
                (
                    !piece->isPinnedX && 
                    !piece->isPinnedY &&
                    !piece->isPinnedDiagonalLeft
                )
            ){
                hasfoundPiece = NULL;
                xx = piece->x,yy = piece->y;
                while(true){
                    if(xx == 0 || yy == 7 || !testCase(piece,--xx,++yy,isForCaseValid,&hasfoundPiece,PINR))
                        break;
                }
                
                /* ----------------------------------------------- */
                hasfoundPiece = NULL;
                xx = piece->x,yy = piece->y;
                while(true){
                    if(xx == 7 || yy == 0 || !testCase(piece,++xx,--yy,isForCaseValid,&hasfoundPiece,PINR))
                        break;
                }
            }
        }
        if(piece->type == QUEEN || piece->type == ROOK){
            if(
                !isForCaseValid || 
                (
                    !piece->isPinnedX && 
                    !piece->isPinnedDiagonalLeft &&
                    !piece->isPinnedDiagonalRight
                )
            ){
                hasfoundPiece = NULL;
                xx = piece->x,yy = piece->y;
                while(true){
                    if(yy == 7 || !testCase(piece,xx,++yy,isForCaseValid,&hasfoundPiece,PINY))
                        break;
                }
                
                /* ----------------------------------------------- */
                hasfoundPiece = NULL;
                xx = piece->x,yy = piece->y;
                while(true){
                    if(yy == 0 || !testCase(piece,xx,--yy,isForCaseValid,&hasfoundPiece,PINY))
                        break;
                }
            }

            /* ----------------------------------------------- */

            if(
                !isForCaseValid || 
                (
                    !piece->isPinnedY && 
                    !piece->isPinnedDiagonalLeft &&
                    !piece->isPinnedDiagonalRight
                )
            ){
                hasfoundPiece = NULL;
                xx = piece->x,yy = piece->y;
                while(true){
                    if(xx == 7 || !testCase(piece,++xx,yy,isForCaseValid,&hasfoundPiece,PINX))
                        break;
                }
                
                /* ----------------------------------------------- */
                hasfoundPiece = NULL;
                xx = piece->x,yy = piece->y;
                while(true){
                    if(xx == 0 || !testCase(piece,--xx,yy,isForCaseValid,&hasfoundPiece,PINX))
                        break;
                }
            }
        }
    }
    
}