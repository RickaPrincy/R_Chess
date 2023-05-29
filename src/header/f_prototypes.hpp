#ifndef __F_PROTOTYPES__
#define __F_PROTOTYPES__

	#include "lib.hpp"
	#include "../var/var.hpp"
	#include "Type.hh"
	#include "Piece.hh"
	#include "Case.hh"
	#include "Input.hh"
	#include "event.hpp"
	#include "background.hpp"
	#include "piecesFunction.hpp"
	#include "pieceSelected.hpp"
	#include "calcul.hpp"
	#include "mouseEvent.hpp"
	#include "casesFunction.hpp"
	#include "mainStruct.hpp"
	
	void Error(char const *text);

	SDL_Window *getWindow();
	SDL_Renderer *getRenderer();

	void LimitFPS(unsigned int limit);

	void firstInit(char const *title,int window_w,int window_h);
	void cleanFirstInit();

	void setIcon(char const *path);

	SDL_Texture *textLoad(char const *Texte,int Taille,SDL_Color color,char const *path);
	void renderCopy(SDL_Texture *image, int x, int y);
	SDL_Texture *imageLoad(char const *path);
	
	
#endif