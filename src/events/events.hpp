#pragma once

#include "../board/board.hpp"

namespace rchess
{
	void handle_case_click(int x, int y, Board *board);
	void reset_selected_piece(Board *board);
}  // namespace rchess
