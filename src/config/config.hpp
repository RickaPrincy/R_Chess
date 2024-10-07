#pragma once

#include <SDL2/SDL_events.h>

namespace rchess
{
	namespace config
	{
		inline constexpr const int WINDOW_SIZE = 568;
		inline constexpr const int BORDER_SIZE = 20;
		inline constexpr const int CASE_SIZE = 66;
		inline constexpr const int PIECE_SIZE = 50;
		inline constexpr const int PADDING_SIZE = CASE_SIZE - PIECE_SIZE;
		inline constexpr const int MAX_COORD_ON_BOARD = 8 * CASE_SIZE + BORDER_SIZE;
		inline constexpr const int MIN_COORD_ON_BOARD = BORDER_SIZE;
		bool is_on_board(const SDL_MouseMotionEvent &event);
	}  // namespace config

}  // namespace rchess
