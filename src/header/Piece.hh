#ifndef __PIECE__
#define __PIECE__

    #include "f_prototypes.hpp"

    class Piece{
        public:
            int x,y,color;
            Type type;
            bool isOnBoard, isSelected, alreadyMove;
    };

#endif