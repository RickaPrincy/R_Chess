#pragma once

#include <SDL2/SDL_events.h>

namespace rchess
{
	namespace constant
	{
		inline constexpr const int UI_WINDOW_SIZE = 568;
		inline constexpr const int UI_BORDER_SIZE = 20;
		inline constexpr const int UI_CASE_SIZE = 66;
		inline constexpr const int UI_PIECE_SIZE = 50;
		inline constexpr const int ROW_COUNT = 8;
		inline constexpr const int COLUMN_COUNT = 8;
		inline constexpr const int PIECES_COUNT = 32;
		inline constexpr const int UI_PADDING_SIZE = UI_CASE_SIZE - UI_PIECE_SIZE;
		inline constexpr const int MAX_COORD_ON_BOARD = ROW_COUNT * UI_CASE_SIZE + UI_BORDER_SIZE;
		inline constexpr const int MIN_COORD_ON_BOARD = UI_BORDER_SIZE;
	}  // namespace constant
}  // namespace rchess
