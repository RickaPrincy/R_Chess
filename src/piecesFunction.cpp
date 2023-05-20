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
        Piece *currentPiece = &pieces.at(i);
        Case *currentCase = NULL;
        currentPiece->color = i < 16 ? BLACK : WHITE;
        currentPiece->isOnBoard = true;
        currentPiece->isSelected = false;
        
        //init positions
        if(i < 16){
            currentPiece->x = i < 8 ? i : i - 8;
            currentPiece->y = i < 8 ? 0 : 1;
        }
        else{
            currentPiece->x = i < 24 ? i - 16 : i - 24;
            currentPiece->y = i < 24 ? 6 : 7;
        }

        currentCase = getCase(currentPiece->x, currentPiece->y);
        currentCase->piece = currentPiece;

        //init pawn type
        if(i > 7 && i < 24){
            currentPiece->type = PAWN;
        }
    }

    //init type for pieces which not a pawn
    pieces.at(0).type = pieces.at(7).type = pieces.at(24).type = pieces.at(31).type = ROOK;
	pieces.at(1).type = pieces.at(6).type = pieces.at(25).type = pieces.at(30).type = KNIGHT;
	pieces.at(2).type = pieces.at(5).type = pieces.at(26).type = pieces.at(29).type = BISHOP;
	pieces.at(3).type = pieces.at(27).type = QUEEN;
	pieces.at(4).type = pieces.at(28).type = KING;
}

Piece *getPiece(int index){
    return &pieces.at(index);
}

//to draw all pieces
void drawPieces(){
    SDL_Rect dest,src;
	dest.w = dest.h = src.w = src.h = PIECE_SIZE;

    for(std::vector<Piece>::size_type i = 0; i < pieces.size(); i++){
        Piece &currentPiece = pieces.at(i);

        //We show the pieces if it's not captured
        if(currentPiece.isOnBoard && !currentPiece.isSelected){
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

            src.x = BORDER_SIZE / 2 + currentPiece.x * CASE_SIZE + 16;
            src.y = BORDER_SIZE / 2 + currentPiece.y * CASE_SIZE + 16;

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