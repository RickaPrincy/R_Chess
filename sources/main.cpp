#include <sdlk/core/app.hpp>

#include "board.hpp"
#include "constant.hpp"

using namespace sdlk;
using namespace constant;

auto main(int argc, char **argv) -> int
{
	app rchess("R_Chess", window_size, window_size);

	board rchess_board(&rchess);

	return rchess.run(argc, argv);
}
