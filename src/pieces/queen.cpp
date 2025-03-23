#include "../board/board.hpp"
#include "pieces.hpp"

namespace rchess
{
	Queen::Queen(PieceColor color, int x, int y) : Piece(PieceType::QUEEN, color, x, y)
	{
	}

	void Queen::calc_possible_moves(Board *board)
	{
		auto cases = board->get_cases();
		// Rook-like moves
		this->explore_direction(1, 0, cases);
		this->explore_direction(-1, 0, cases);
		this->explore_direction(0, 1, cases);
		this->explore_direction(0, -1, cases);

		// Bishop-like moves
		this->explore_direction(1, 1, cases);
		this->explore_direction(1, -1, cases);
		this->explore_direction(-1, 1, cases);
		this->explore_direction(-1, -1, cases);
	}
}  // namespace rchess
