#ifndef __CASE__
#define __CASE__

    #include "../header/f_prototypes.hpp"

    class Case{
        public:
            Piece *piece = NULL;
            bool isValid = false;
            vector<Piece*> attackerWhite, attackerBlack;
            bool isEmpty();
    };

#endif