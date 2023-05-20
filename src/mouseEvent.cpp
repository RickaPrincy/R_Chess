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
        cout << "out the chessboard" << endl;
        return;
    }

	if(input->left == CLICKED || input->left == RELEASED){
        
        //to know the x and y case[x][y] clicked
        xCase = (input->mouseX - BORDER_SIZE) / CASE_SIZE;
        yCase = (input->mouseY - BORDER_SIZE) / CASE_SIZE;
        cout << "xCase : " << xCase << " et yCase : " << yCase << endl;
        
        if(input->left == CLICKED){
            if(pieceSelected == NULL){
                if(getCase(xCase,yCase)->piece != NULL){
                    pieceSelected = getCase(xCase,yCase)->piece;
                    pieceSelected->isSelected = true;
                }
            }else{
                if(getCase(xCase,yCase)->piece != NULL){
                    pieceSelected = getCase(xCase,yCase)->piece;
                    pieceSelected->isSelected = true;
                }
            }
        }
    }

}