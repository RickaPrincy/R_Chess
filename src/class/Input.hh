#ifndef __INPUT__
#define __INPUT__ 
	
	#include "../header/f_prototypes.hpp"
	
    enum MouseStatus{
        CLICKED,
        RELEASED,
        NOT_CLICKED
    };

	class Input{
	    public:
            int mouseX,mouseY;
            MouseStatus left = NOT_CLICKED ,right = NOT_CLICKED;
            bool isOnWindow,isOnMove;
	};

#endif