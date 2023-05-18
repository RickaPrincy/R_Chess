#include "header/f_prototypes.hpp"

int main(int argc,char *argv[]){

	firstInit("R_Chess",WINDOW_W,WINDOW_H);
	SDL_Rect dest,src;
	SDL_Texture *background = imageLoad("graphics/chessBoard.jpg");
	SDL_Texture *piece = imageLoad("graphics/pieces.png");
	
	dest.y = PIECE_SIZE;
	dest.x = 1;
	src.x = src.y = BORDER_SIZE + 8;
	dest.w = dest.h = src.w = src.h= PIECE_SIZE;
	renderCopy(background,0,0);
	for (int i = 0; i < 8; i++)
	{
		dest.x = PIECE_SIZE * i;
		src.x = BORDER_SIZE + 8 + CASE_SIZE * i;
		SDL_RenderCopy(getRenderer(),piece,&dest,&src);
	}
	
	SDL_RenderPresent(getRenderer());
	SDL_Delay(6000);
	cleanFirstInit();
	return 0;
}