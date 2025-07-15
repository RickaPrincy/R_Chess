#include "../board/board.hpp"
#include "pieces.hpp"

namespace rchess
{
	Bishop::Bishop(PieceColor color, int x, int y) : Piece(PieceType::BISHOP, color, x, y)
	{
	}

	void Bishop::calc_possible_moves(Board *board)
	{
		auto cases = board->get_cases();
		this->explore_direction(1, 1, cases);
		this->explore_direction(1, -1, cases);
		this->explore_direction(-1, 1, cases);
		this->explore_direction(-1, -1, cases);
	}
}  // namespace rchess
