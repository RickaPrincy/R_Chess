#include "header/f_prototypes.hpp"

void handlerMouseEvent(){
    Input *input = getInput();
    Piece *pieceSelected = getPieceSelected();
    int xCase,yCase;

    //it's not necessary to calcul everything if the mouse isn't on the board
    if(
        input->mouseX < BORDER_SIZE ||
        input->mouseY < BORDER_SIZE ||
        input->mouseX > BORDER_SIZE + 8 * CASE_SIZE ||
        input->mouseY > BORDER_SIZE + 8 * CASE_SIZE
    ){
        if(pieceSelected != NULL){
            initPieceSelected();
        }
        return;
    }

	if(input->left == CLICKED || (input->left == RELEASED && input->isOnMove)){

        //to know the x and y case[x][y] clicked
        xCase = (input->mouseX - BORDER_SIZE) / CASE_SIZE;
        yCase = (input->mouseY - BORDER_SIZE) / CASE_SIZE;

        Case *currentCase = getCase(xCase,yCase);

        if(input->left == CLICKED && pieceSelected == NULL && !currentCase->isEmpty()){
            makeSelected(currentCase->piece);
        }
        else if(pieceSelected != NULL){
            if(currentCase->isEmpty()){
                if(currentCase->isValid)
                    changePosition(xCase, yCase);
                else
                    initPieceSelected();
            }
            else{
                if(currentCase->piece->color == pieceSelected->color){
                    if(input->left == CLICKED){
                        switchSelectedPiece(currentCase->piece);
                    }
                    else{
                        initPieceSelected();
                    }
                }
                else{
                    if(currentCase->isValid){
                        capture(currentCase->piece,xCase, yCase);
                    }
                    else{
                        initPieceSelected();
                    }
                }
            }
        }

        input->left = NOT_CLICKED;
    }

}