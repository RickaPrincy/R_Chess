#ifndef  __PIECE_SELECTED__
#define __PIECE_SELECTED__

    #include "f_prototypes.hpp"

    Piece *getPieceSelected();
    void initPieceSelected();
    void changePosition(int, int);
    void makeSelected(Piece*);
    void switchSelectedPiece(Piece*);
    void capture(int,int);
    void resetAfterChange();
    void drawPieceSelected();

#endif