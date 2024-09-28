#include "config.hpp"

namespace rchess
{
	using namespace rchess::config;

	bool config::is_on_board(const SDL_MouseMotionEvent &event)
	{
		return event.x < MAX_COORD_ON_BOARD && event.y < MAX_COORD_ON_BOARD && event.x > MIN_COORD_ON_BOARD &&
			   event.y > MIN_COORD_ON_BOARD;
	}
}  // namespace rchess
