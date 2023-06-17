#include "header/f_prototypes.hpp"

static short turn = WHITE;

short *getTurn(){
    return &turn;
}


void handlerMouseEvent(){
    Input *input = getInput();
    Piece *pieceSelected = getPieceSelected();
    int xCase,yCase;

    //it's not necessary to calcul everything if the mouse isn't on the board
    if(
        (input->mouseX < BORDER_SIZE ||
        input->mouseY < BORDER_SIZE ||
        input->mouseX > BORDER_SIZE + 8 * CASE_SIZE ||
        input->mouseY > BORDER_SIZE + 8 * CASE_SIZE )
        && input->isOnMove
        && pieceSelected != NULL
    ){
        initPieceSelected();
        return;
    }

	if(input->left == CLICKED || (input->left == RELEASED && input->isOnMove)){

        //to know the x and y case[x][y] clicked
        xCase = (input->mouseX - BORDER_SIZE) / CASE_SIZE;
        yCase = (input->mouseY - BORDER_SIZE) / CASE_SIZE;

        Case *currentCase = getCase(xCase,yCase);

        if(input->left == CLICKED && pieceSelected == NULL && !currentCase->isEmpty()){
            if(currentCase->piece->color == *getTurn()){
                makeSelected(currentCase->piece);
                if(getPieceSelected()->type == KING)
                    calculKing(getPieceSelected(),CASE_VALID);
                else
                    calcul(getPieceSelected(),CASE_VALID);
            }
        }
        else if(pieceSelected != NULL){
            if(currentCase->isEmpty()){
                if(currentCase->isValid){
                    changePosition(xCase, yCase);
                    resetAfterChange();
                }
                else if(input->left == CLICKED)
                    initPieceSelected();
            }
            else{
                if(currentCase->piece->color == pieceSelected->color){
                    if(input->left == CLICKED){
                        switchSelectedPiece(currentCase->piece);
                        if(getPieceSelected()->type == KING)
                            calculKing(getPieceSelected(),CASE_VALID);
                        else
                            calcul(getPieceSelected(),CASE_VALID);
                    }
                }
                else if(currentCase->isValid){
                    capture(xCase, yCase);
                    resetAfterChange();
                }
                else if(input->left == CLICKED)
                    initPieceSelected();
            }
        }

        input->isOnMove = false;    
        input->left = NOT_CLICKED;
    }

}