#include "header/f_prototypes.hpp"

static std::vector<std::vector<Case>> cases(8, std::vector<Case>(8));

Case *getCase(int x, int y){
    return &cases[x][y];
}

void initCases(short typeOfInit) {
    std::for_each(cases.begin(), cases.end(), [typeOfInit](std::vector<Case>& row) {
        std::for_each(row.begin(), row.end(), [typeOfInit](Case& c) {
            if(typeOfInit == LIST_OF_ATTACKER){
                c.attackerWhite.clear();
                c.attackerBlack.clear();
            }
            else if(typeOfInit == PIECE){
                c.attackerWhite.clear();
                c.attackerBlack.clear();
                c.piece = NULL;
                c.isValid = false;
            }
            else if(typeOfInit == LIST_AND_VALID){
                c.attackerWhite.clear();
                c.attackerBlack.clear();
                c.isValid = false;
            }
            else{
                c.isValid = false;
            }
        });
    });
}

void drawHollowRect(SDL_Rect rect, int thickness) {
    SDL_RenderDrawRect(getRenderer(), &rect);
    
    SDL_Rect tempRect = { rect.x, rect.y, rect.w, thickness };
    SDL_RenderFillRect(getRenderer(), &tempRect);
    
    tempRect = { rect.x, rect.y + rect.h - thickness, rect.w, thickness };
    SDL_RenderFillRect(getRenderer(), &tempRect);
    
    tempRect = { rect.x, rect.y + thickness, thickness, rect.h - thickness * 2 };
    SDL_RenderFillRect(getRenderer(), &tempRect);
    
    tempRect = { rect.x + rect.w - thickness, rect.y + thickness, thickness, rect.h - thickness * 2 };
    SDL_RenderFillRect(getRenderer(), &tempRect);
}

void drawCasesValid(){
    SDL_Rect rect;

    for(int i = 0; i< 8; i++){
        for(int j = 0; j < 8; j++){
            if(getCase(i,j)->isValid){
                if( getCase(i,j)->isEmpty()){
                    rect.w = rect.h =  18;
                    rect.x = BORDER_SIZE + CASE_SIZE / 2 - 9 - 2 + i * CASE_SIZE;
                    rect.y = BORDER_SIZE + CASE_SIZE / 2 - 9 - 2 + j * CASE_SIZE;
                    SDL_SetRenderDrawColor(getRenderer(),255,255,0,255);
                }
                else{
                    rect.w = rect.h =  CASE_SIZE;
                    rect.x = BORDER_SIZE - 2 + i * CASE_SIZE;
                    rect.y = BORDER_SIZE - 2 + j * CASE_SIZE;
                    SDL_SetRenderDrawColor(getRenderer(),255,15,15,255);
                }

                SDL_RenderFillRect(getRenderer(), &rect);
            }
        }
    }
}

//draw a purple on king if there is a check
void drawCheck(){
    Piece *kingBlack = getPiece(4), *kingWhite = getPiece(28);
    SDL_Rect rect;
    rect.w = rect.h =  CASE_SIZE;
    SDL_SetRenderDrawColor(getRenderer(),196,4,196,255);

    if(isThereACheck() > 0){
        if(*getTurn() == WHITE){
            rect.x = BORDER_SIZE - 2 + kingWhite->x * CASE_SIZE;
            rect.y = BORDER_SIZE - 2 + kingWhite->y * CASE_SIZE;
            SDL_RenderFillRect(getRenderer(), &rect);
        }
        else{
            rect.x = BORDER_SIZE - 2 + kingBlack->x * CASE_SIZE;
            rect.y = BORDER_SIZE - 2 + kingBlack->y * CASE_SIZE;
            SDL_RenderFillRect(getRenderer(), &rect);
        }
    }  

}


//draw some color a case selected
void drawCasesSelected(){
    if(getPieceSelected() != NULL){

        SDL_Rect rect;
        rect.w = rect.h =  CASE_SIZE;
        rect.x = BORDER_SIZE - 2 + getPieceSelected()->x * CASE_SIZE;
        rect.y = BORDER_SIZE - 2 + getPieceSelected()->y * CASE_SIZE;

		SDL_SetRenderDrawColor(getRenderer(),255,242,0,255);
		drawHollowRect(rect,3);
    }
}