#include "header/f_prototypes.hpp"

static std::vector<std::vector<Case>> cases(8, std::vector<Case>(8));

Case *getCase(int x, int y){
    return &cases[x][y];
}

void initCases() {
    std::for_each(cases.begin(), cases.end(), [](std::vector<Case>& row) {
        std::for_each(row.begin(), row.end(), [](Case& c) {
            c.piece = NULL;
        });
    });
}

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
