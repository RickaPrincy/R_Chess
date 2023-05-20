#ifndef  __PIECES_FUNCTION__
#define __PIECES_FUNCTION__

    #include "f_prototypes.hpp"
    void loadPieces();
    void initPieces();
    Piece *getPiece(int index);
    SDL_Texture *getPiecesImage();
    int getImagePosition(Type);
    void drawPieces();
    void cleanPieces();

#endif