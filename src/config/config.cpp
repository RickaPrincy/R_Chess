#include "config.hpp"

namespace rchess
{
	bool config::is_on_board(const SDL_MouseMotionEvent &event)
	{
		return event.x < config::MAX_COORD_ON_BOARD || event.y < config::MAX_COORD_ON_BOARD ||
			   event.x > config::MAX_COORD_ON_BOARD || event.y > config::MAX_COORD_ON_BOARD;
	}
}  // namespace rchess
