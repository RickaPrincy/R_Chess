#ifndef  __CASE_FUNCTION__
#define __CASE_FUNCTION__

    #include "f_prototypes.hpp"
    Case *getCase(int x, int y);
    void initCases(short);
    void drawHollowRect(SDL_Rect,int);
    void drawCasesValid();
    void drawCheck();
    void drawCasesSelected();
#endif