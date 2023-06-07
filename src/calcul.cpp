#include "header/f_prototypes.hpp"

//make a temporary change to know if there is a check or not after a move
bool temporaryChange(Piece *piece,int x, int y){
    int originX = piece->x, originY = piece->y;
    bool result = true;
    Piece *blackKing = getPiece(4);
    Piece *whiteKing = getPiece(28);
    Piece *temp = NULL;

    if(getCase(x,y)->isEmpty()){
        changePosition(x,y);
    }
    else{
        temp = getCase(x,y)->piece;
        capture(getCase(x,y)->piece,x,y);
    }

    globalCalcul();
    if(*getTurn() == WHITE){
        if(getCase(blackKing->x,blackKing->y)->attackerWhite.size() > 0){
            result = false;
        }
    }
    else if(*getTurn() == BLACK){
        if(getCase(whiteKing->x,whiteKing->y)->attackerBlack.size() > 0){
            result = false;
        }
    }

    *getTurn() = *getTurn() == WHITE ? BLACK : WHITE; 
    
    makeSelected(piece);
    changePosition(originX,originY);
    
    if(temp != NULL){
        temp->isOnBoard = false;
    }

    globalCalcul();
    return result;
}

//test if one case is a case valid for a selected piece
bool testCase(Piece *piece,int x, int y,bool isForCaseValid){
    if(getCase(x,y)->isEmpty() || getCase(x,y)->piece->color != piece->color){
        
        if(isForCaseValid){
            if(temporaryChange(piece,x,y)){
                getCase(x,y)->isValid = true;
            }else{
                getCase(x,y)->isValid = false;
            }
        }else{
            if(piece->color == WHITE){
                getCase(x,y)->attackerWhite.push_back(piece);
            }else{
                getCase(x,y)->attackerBlack.push_back(piece);
            }
        }

        return getCase(x,y)->isEmpty();
    }
    else
        return false;
}

//calcul all case attacked
void globalCalcul(){
    cout << "calcul global" << endl;
    initCases(LIST_OF_ATTACKER);

    for(int i = 0; i < 32; i++){
        calcul(getPiece(i),false);
    }
}

void calcul(Piece *piece, bool isForCaseValid){
    int xx, yy;
    
    if(piece->type == PAWN){

        int increment = piece->color == WHITE ? -1 : 1;
        int y = piece->y + increment;
        
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
            testCase(piece,piece->x + 1,y,isForCaseValid);
        }
        /* ----------------------------------------------------- */
        if(piece->x > 0 && !getCase(piece->x - 1,y)->isEmpty() && getCase(piece->x - 1,y)->piece->color != piece->color){
            testCase(piece,piece->x - 1,y,isForCaseValid);
        }
    }
    else if(piece->type == KNIGHT){
		if(piece->y < 6){
			
            if(piece->x < 7)
                testCase(piece,piece->x + 1, piece->y + 2,isForCaseValid);
			if(piece->x > 0)
               	testCase(piece,piece->x - 1, piece->y + 2,isForCaseValid);
		
        }

		/*---------------------------------------------------*/

		if(piece->y > 1){
			if(piece->x < 7)
                testCase(piece,piece->x + 1, piece->y - 2,isForCaseValid);
			if(piece->x > 0)
                testCase(piece,piece->x - 1, piece->y - 2,isForCaseValid);
		}

		/*---------------------------------------------------*/

		if(piece->x < 6){

			if(piece->y < 7)
                testCase(piece,piece->x + 2, piece->y + 1,isForCaseValid);
			if(piece->y > 0)
				testCase(piece,piece->x + 2, piece->y - 1,isForCaseValid);
		}

		/*---------------------------------------------------*/

		if(piece->x > 1){

			if(piece->y < 7)
               	testCase(piece,piece->x - 2, piece->y + 1,isForCaseValid);
			if(piece->y > 0)
                testCase(piece,piece->x - 2, piece->y - 1,isForCaseValid);
		}
    }
    else{
        if(piece->type == QUEEN || piece->type == BISHOP){
            
            xx = piece->x,yy = piece->y;
            while(true){
                if(xx == 7 || yy == 7 || !testCase(piece,++xx,++yy,isForCaseValid))
                    break;
            }
            
            /* ----------------------------------------------- */
            xx = piece->x,yy = piece->y;
            while(true){
                if(xx == 0 || yy == 0 || !testCase(piece,--xx,--yy,isForCaseValid))
                    break;
            }

            /* ----------------------------------------------- */
            xx = piece->x,yy = piece->y;
            while(true){
                if(xx == 0 || yy == 7 || !!testCase(piece,--xx,++yy,isForCaseValid))
                    break;
            }
            
            /* ----------------------------------------------- */
            xx = piece->x,yy = piece->y;
            while(true){
                if(xx == 7 || yy == 0 || !testCase(piece,++xx,--yy,isForCaseValid))
                    break;
            }
        }
        if(piece->type == QUEEN || piece->type == ROOK){
            xx = piece->x,yy = piece->y;
            while(true){
                if(yy == 7 || !testCase(piece,xx,++yy,isForCaseValid))
                    break;
            }
            
            /* ----------------------------------------------- */
            xx = piece->x,yy = piece->y;
            while(true){
                if(yy == 0 || !testCase(piece,xx,--yy,isForCaseValid))
                    break;
            }
            /* ----------------------------------------------- */
            xx = piece->x,yy = piece->y;
            while(true){
                if(xx == 7 || !testCase(piece,++xx,yy,isForCaseValid))
                    break;
            }
            
            /* ----------------------------------------------- */
            xx = piece->x,yy = piece->y;
            while(true){
                if(xx == 0 || !testCase(piece,--xx,yy,isForCaseValid))
                    break;
            }
        }
    }
    
}