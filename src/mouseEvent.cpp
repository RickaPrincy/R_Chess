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

	if(input->left == CLICKED || input->left == RELEASED){

        //to know the x and y case[x][y] clicked
        xCase = (input->mouseX - BORDER_SIZE) / CASE_SIZE;
        yCase = (input->mouseY - BORDER_SIZE) / CASE_SIZE;

        if(input->left == CLICKED){
            Case *currentCase = getCase(xCase,yCase);

            if(pieceSelected == NULL && !currentCase->isEmpty()){
                makeSelected(currentCase->piece);
            }
            else if(pieceSelected != NULL){
                if(currentCase->isEmpty()){
                    changePosition(xCase, yCase);
                }
                else{
                    capture(currentCase->piece,xCase, yCase);
                }
            }
        }

        input->left = NOT_CLICKED;
    }

}