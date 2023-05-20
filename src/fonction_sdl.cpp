#include "header/f_prototypes.hpp"

/*-----------------------------------------------*/

static SDL_Renderer *renderer = NULL;
static SDL_Window *window = NULL;
static SDL_Surface *icon = NULL;

/*-----------------------------------------------*/
void Error(char const *text){
	SDL_Log("Error of : %s caused by  : %s",text,SDL_GetError());
}

/*-----------------------------------------*/

SDL_Window *getWindow(){
	return window;
}

/*-----------------------------------------*/

SDL_Renderer *getRenderer(){
	return renderer;
}

/*-----------------------------------------------*/

void LimitFPS(unsigned int limit){
	unsigned int ticks = SDL_GetTicks();

	if(limit < ticks)
		return;
	else if(limit > ticks + FPS_LIMIT)
		SDL_Delay(FPS_LIMIT);
	else
		SDL_Delay(limit - ticks);
}

/*-----------------------------------------------*/

void firstInit(char const *title,int window_w,int window_h){
	if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0){
		Error("Initialisation : sdl");
		exit(EXIT_FAILURE);
	}
	/*-----------------------------------------*/

	window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,window_w,window_h,SDL_WINDOW_SHOWN);
	if(window == NULL){
		Error("Creation : fenetre");
		exit(EXIT_FAILURE);
	}

	/*-----------------------------------------*/

	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if(renderer == NULL){
		Error("Creation :  rendu");
		exit(EXIT_FAILURE);
	}

	/*-----------------------------------------*/

	//Initialisation du chargement des images png avec SDL_Image 2
	int imgFlags = IMG_INIT_PNG;
	
	if( !( IMG_Init( imgFlags ) & imgFlags ) ){
		Error("Initialisation : sdl_image");
		exit(EXIT_FAILURE);
	}

	/*-----------------------------------------*/

	//Initialisation de la  SDL_TTF 2 
	if (TTF_Init() < 0){
		Error("Initialisation : sdl_ttf");
		exit(EXIT_FAILURE);
	}


	SDL_RenderPresent(renderer);
}

/*-----------------------------------------------*/

void cleanFirstInit(){
	if(icon != NULL){
		SDL_FreeSurface(icon);
		cout << "Icon Destroyed" << endl;
	}

	if(renderer != NULL){
		SDL_DestroyRenderer(renderer);
		cout << "Renderer Destroyed" << endl;
	}

	if(window != NULL){
		SDL_DestroyWindow(window);
		cout << "Window Destroyed" << endl;
	}

	TTF_Quit();
	SDL_Quit();
}

/*-----------------------------------------------*/

void setIcon(char const *path){
	icon = IMG_Load(path);
	if(icon == NULL){
		Error("Icon");
		exit(EXIT_FAILURE);
	}

	SDL_SetWindowIcon(window,icon);
}

/*-----------------------------------------------*/

SDL_Texture *imageLoad(char const *path){

	SDL_Surface *image = NULL;
	SDL_Texture *texture = NULL;

	image = IMG_Load(path);

	if(image == NULL){
		Error("Creation of a surface");
		exit(EXIT_FAILURE);
	}	

	texture = SDL_CreateTextureFromSurface(renderer,image);
	SDL_FreeSurface(image);

	if(texture == NULL){
		Error("Creation of a texture");
		exit(EXIT_FAILURE);
	}
	return texture;
}

/*-----------------------------------------*/

void renderCopy(SDL_Texture *image, int x, int y){
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;

	if(SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h) != 0){
		
		Error("SDL_QueryTexture : RenderCopy");
		exit(EXIT_FAILURE);
	}

	if(SDL_RenderCopy(renderer, image, NULL, &dest) != 0){
		Error("SDL_RenderCopy ; RenderCopy");
		exit(EXIT_FAILURE);
	}
}

/*-----------------------------------------*/

SDL_Texture *textLoad(char const *Texte,int Taille,SDL_Color color,char const *path){
	SDL_Surface *Surface = NULL;
	SDL_Texture *Texture = NULL;

	TTF_Font *font = TTF_OpenFont(path,Taille);
	Surface = TTF_RenderText_Solid(font,Texte,color);
	TTF_CloseFont(font);

	if(Surface == NULL){
		Error("Surface : TextLoad()");
		exit(EXIT_FAILURE);
	}

	Texture = SDL_CreateTextureFromSurface(renderer,Surface);
	SDL_FreeSurface(Surface);

	if(Texture == NULL){
		Error("Texture : TextLoad()");
		exit(EXIT_FAILURE);
	}

	return Texture;
}
