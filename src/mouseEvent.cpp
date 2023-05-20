#include "header/f_prototypes.hpp"

void handlerMouseEvent(){
    Input *input = getInput();
    Piece *pieceSelected = getPieceSelected();
    int xCase,yCase;
    
    if(
        input->mouseX < BORDER_SIZE ||
        input->mouseY < BORDER_SIZE ||
        input->mouseX > BORDER_SIZE + 8 * CASE_SIZE ||
        input->mouseY > BORDER_SIZE + 8 * CASE_SIZE 
    ){
        cout << "out the chessboard" << endl;
        return;
    }
    
    //to know the x and y case[x][y] clicked
    xCase = (input->mouseX - BORDER_SIZE) / CASE_SIZE;
    yCase = (input->mouseY - BORDER_SIZE) / CASE_SIZE;

	if(input->left == CLICKED){
        cout << "xCase : " << xCase << " et yCase : " << yCase << endl;
    }

}