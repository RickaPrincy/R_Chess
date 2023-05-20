#include "header/f_prototypes.hpp"

static SDL_Texture *background = NULL;

void loadBackground(){
    background = imageLoad("graphics/background.jpg");
    cout << "Background loaded" << endl;
}

void drawBackground(){
    renderCopy(background,0,0);    
}

void cleanBackground(){
    if(background != NULL){
        SDL_DestroyTexture(background);
        cout << "Background Destroyed" << endl;
    }    
}