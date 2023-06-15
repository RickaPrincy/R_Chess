#ifndef  __CASE_FUNCTION__
#define __CASE_FUNCTION__

    #include "f_prototypes.hpp"
    Case *getCase(int x, int y);
    std::vector<std::vector<Case>> getAllCase();
    void initCases(short);
    void drawHollowRect(SDL_Rect,int);
    void drawCasesValid();
    void drawCheck();
#endif