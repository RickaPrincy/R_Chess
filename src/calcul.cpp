#include "header/f_prototypes.hpp"

void testCase(Piece *piece,int x, int y){
    if(getCase(x,y)->isEmpty()|| getCase(x,y)->piece->color != piece->color){
        getCase(x,y)->isValid = true;
    }
}
void calcul(){
    Piece *piece = getPieceSelected();
    int increment = piece->color == WHITE ? -1 : 1;
    int y = piece->y + increment;
    int xx = piece->x, yy = piece->y;

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
    else if(piece->type == KNIGHT){
		if(piece->y < 6){
			
            if(piece->x < 7)
                testCase(piece,xx + 1, yy + 2);
			if(piece->x > 0)
               	testCase(piece,xx - 1, yy + 2);
		
        }

		/*---------------------------------------------------*/

		if(piece->y > 1){
			if(piece->x < 7)
                testCase(piece,xx + 1, yy - 2);
			if(piece->x > 0)
                testCase(piece,xx - 1, yy - 2);
		}

		/*---------------------------------------------------*/

		if(piece->x < 6){

			if(piece->y < 7)
                testCase(piece,xx + 2, yy + 1);
			if(piece->y > 0)
				testCase(piece,xx + 2, yy - 1);
		}

		/*---------------------------------------------------*/

		if(piece->x > 1){

			if(piece->y < 7)
               	testCase(piece,xx - 2, yy + 1);
			if(piece->y > 0)
                testCase(piece,xx - 2, yy - 1);
		}
    }
}