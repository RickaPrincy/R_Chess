#include "header/f_prototypes.hpp"

static std::vector<Piece> pieces(32);
static SDL_Texture *pieceImage = NULL;

//We charge the image
void loadPieces(){
    pieceImage = imageLoad("graphics/pieces.png");
    cout << "Pieces loaded" << endl;
}

//init all Pieces
void initPieces(){

    for(std::vector<Piece>::size_type i = 0; i < pieces.size(); i++){
        Piece &currentPiece = pieces.at(i);
        currentPiece.color = i < 16 ? WHITE : BLACK;
        currentPiece.isOnBoard = true;
        
        //init positions
        if(i < 16){
            currentPiece.x = i < 8 ? i + 1 : i - 7;
            currentPiece.y = i < 8 ? 2 : 1;
        }
        else{
            currentPiece.x = i < 24 ? i - 15 : i - 23;
            currentPiece.y = i < 24 ? 7 : 8;
        }

        //init pawn type
        if(i < 8 || ( i >=16  && i < 24)){
            currentPiece.type = PAWN;
        }
    }

    //init type for pieces which not a pawn
    pieces.at(8).type = pieces.at(15).type = pieces.at(24).type = pieces.at(31).type = ROOK;
	pieces.at(9).type = pieces.at(14).type = pieces.at(25).type = pieces.at(30).type = KNIGHT;
	pieces.at(10).type = pieces.at(13).type = pieces.at(26).type = pieces.at(29).type = BISHOP;
	pieces.at(11).type = pieces.at(27).type = QUEEN;
	pieces.at(12).type = pieces.at(28).type = KING;
}

//to draw all pieces
void drawPieces(){
    SDL_Rect dest,src;
	dest.w = dest.h = src.w = src.h = PIECE_SIZE;

    for(std::vector<Piece>::size_type i = 0; i < pieces.size(); i++){
        Piece &currentPiece = pieces.at(i);

        //We show the pieces if it's not captured
        if(currentPiece.isOnBoard){
            switch(currentPiece.type){
				case ROOK: dest.x = 0;
				    break;
				case KNIGHT: dest.x = 50;
				    break;
				case BISHOP: dest.x = 100;
				    break;
				case QUEEN: dest.x = 150;
				    break;
				case KING: dest.x = 200;
				    break;
				default: dest.x = 250;
					break; 
			}
            
            dest.y = currentPiece.color == WHITE ? 0 : 50;

            src.x = BORDER_SIZE / 2 + (currentPiece.x - 1) * CASE_SIZE + 16;
            src.y = BORDER_SIZE / 2 + (8 - currentPiece.y) * CASE_SIZE + 16;

            SDL_RenderCopy(getRenderer(),pieceImage,&dest,&src);
		}
	}
}

//we destroy the texture at the end
void cleanPieces(){
    if(pieceImage != NULL){
        SDL_DestroyTexture(pieceImage);
        cout << "Pieces Destroyed" << endl;
    }    
}