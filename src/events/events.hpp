#pragma once

#include "../board/board.hpp"

namespace rchess
{
	void handle_case_click(Board *board, int x, int y);
	void reset_selected_piece(Board *board);
	void move_piece_position(Board *board, std::shared_ptr<Piece> piece, int x, int y);
}  // namespace rchess
