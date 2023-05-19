#include "header/event.hpp"

Input input;

void handlerEvent(){
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		
        switch (event.type){	
            case SDL_QUIT:
				program_launched = SDL_FALSE;
			break;
            case SDL_MOUSEMOTION:	
				input.mouseX = event.motion.x;
				input.mouseY = event.motion.y;

				if((event.motion.state & SDL_BUTTON_LEFT))
					input.isOnMove = true;
				else
					input.isOnMove = false;
			continue;
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT)
					input.left = CLICKED;
				else if(event.button.button == SDL_BUTTON_RIGHT)
					input.right = CLICKED;
			break;
			case SDL_MOUSEBUTTONUP:
				if(event.button.button == SDL_BUTTON_LEFT)
					input.left = RELEASED;
				else if(event.button.button == SDL_BUTTON_RIGHT)
					input.right = RELEASED;
			break;
			default:
				input.isOnMove = false;
				input.left = RELEASED;
				input.right = RELEASED;
			break;
		}
	}
}