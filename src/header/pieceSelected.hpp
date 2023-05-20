#ifndef  __PIECE_SELECTED__
#define __PIECE_SELECTED__

    #include "f_prototypes.hpp"

    Piece *getPieceSelected();
    void initPieceSelected();
    void changePosition(int, int);
    void makeSelected(Piece*);
    void capture(Piece*,int,int);

#endif