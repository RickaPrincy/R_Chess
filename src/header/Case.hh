#ifndef __CASE__
#define __CASE__

    #include "f_prototypes.hpp"

    class Case{
        public:
            Piece *piece = NULL;
            bool isValid = false;
            bool isEmpty();
    };

#endif