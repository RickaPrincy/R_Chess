#ifndef __PIECE__
#define __PIECE__

    #include "f_prototypes.hpp"

    class Piece{
        public:
            int x,y,color;
            Type type;
            bool isOnBoard;
            bool isSelected;
            int attacker = 0, protection = 0;
    };

#endif