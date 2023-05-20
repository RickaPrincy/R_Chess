#include "header/f_prototypes.hpp"
#include "header/event.hpp"

static SDL_bool program_launched = SDL_TRUE;

SDL_bool *getProgramStatus(){
	return &program_launched;
}

int main(int argc,char *argv[]){
	atexit(cleanEverything);
	firstInit("R_Chess",WINDOW_W,WINDOW_H);
	unsigned int limit = SDL_GetTicks();

	//loading
	load();

	//initisalisation
	init();
	
	while(program_launched){
		
		//render everything
		draw();
		
		//handler event
		handlerEvent();

		handlerMouseEvent();

		LimitFPS(limit);
	}
	return EXIT_SUCCESS;
}