#include "header/f_prototypes.hpp"
#include "header/event.hpp"

SDL_bool program_launched = SDL_TRUE;
int main(int argc,char *argv[]){

	firstInit("R_Chess",WINDOW_W,WINDOW_H);
	unsigned int limit = SDL_GetTicks();

	//loading
	load();

	while(program_launched){
		
		//render everything
		draw();
		
		//handler event
		handlerEvent();

		LimitFPS(limit);
	}

	cleanEverything();
	return EXIT_SUCCESS;
}