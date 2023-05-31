#include "header/f_prototypes.hpp"

bool testCase(int x, int y){
    Piece *piece = getPieceSelected();
    if(getCase(x,y)->isEmpty() || getCase(x,y)->piece->color != piece->color){
        getCase(x,y)->isValid = true;
        return getCase(x,y)->isEmpty();
    }
    else
        return false;
}
void calcul(){
    Piece *piece = getPieceSelected();
    
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
            getCase(piece->x + 1,y)->isValid = true;
        }
        /* ----------------------------------------------------- */
        if(piece->x > 0 && !getCase(piece->x - 1,y)->isEmpty() && getCase(piece->x - 1,y)->piece->color != piece->color){
            getCase(piece->x - 1,y)->isValid = true;
        }
    }
    else if(piece->type == KNIGHT){
		if(piece->y < 6){
			
            if(piece->x < 7)
                testCase(piece->x + 1, piece->y + 2);/* ----------------------------------------------- */
			if(piece->x > 0)
               	testCase(piece->x - 1, piece->y + 2);
		
        }

		/*---------------------------------------------------*/

		if(piece->y > 1){
			if(piece->x < 7)
                testCase(piece->x + 1, piece->y - 2);
			if(piece->x > 0)
                testCase(piece->x - 1, piece->y - 2);
		}

		/*---------------------------------------------------*/

		if(piece->x < 6){

			if(piece->y < 7)
                testCase(piece->x + 2, piece->y + 1);
			if(piece->y > 0)
				testCase(piece->x + 2, piece->y - 1);
		}

		/*---------------------------------------------------*/

		if(piece->x > 1){

			if(piece->y < 7)
               	testCase(piece->x - 2, piece->y + 1);
			if(piece->y > 0)
                testCase(piece->x - 2, piece->y - 1);
		}
    }
    else{
        if(piece->type == QUEEN || piece->type == BISHOP){
            
            int xx = piece->x,yy = piece->y;
            while(true){
                if(xx == 7 || yy == 7 || !testCase(++xx,++yy))
                    break;
            }
            
            /* ----------------------------------------------- */
            xx = piece->x,yy = piece->y;
            while(true){
                if(xx == 0 || yy == 0 || !testCase(--xx,--yy))
                    break;
            }

            /* ----------------------------------------------- */
            xx = piece->x,yy = piece->y;
            while(true){
                if(xx == 0 || yy == 7 || !testCase(--xx,++yy))
                    break;
            }
            
            /* ----------------------------------------------- */
            xx = piece->x,yy = piece->y;
            while(true){
                if(xx == 7 || yy == 0 || !testCase(++xx,--yy))
                    break;
            }
        }
    }
}