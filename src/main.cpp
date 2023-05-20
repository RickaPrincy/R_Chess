#include "header/f_prototypes.hpp"
#include "header/event.hpp"

static SDL_bool program_launched = SDL_TRUE;

SDL_bool *getProgramStatus(){
	return &program_launched;
}

int main(int argc,char *argv[]){
	firstInit("R_Chess",WINDOW_W,WINDOW_H);
	unsigned int limit = SDL_GetTicks();
	atexit(cleanEverything);

	//loading
	load();

	//initisalisation
	init();
	
	while(program_launched){
		
		//render everything
		draw();
		
		//handler event
		handlerEvent();

		//handler mouse :  click and move 
		handlerMouseEvent();

		LimitFPS(limit);
	}
	return EXIT_SUCCESS;
}