#include "header/f_prototypes.hpp"

static std::vector<std::vector<Case>> cases(8, std::vector<Case>(8));

Case *getCase(int x, int y){
    return &cases[x][y];
}