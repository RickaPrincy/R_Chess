#include "../board/board.hpp"
#include "../constant.hpp"
#include "pieces.hpp"

namespace rchess
{
	using namespace constant;
	Rook::Rook(PieceColor color, int x, int y) : Piece(PieceType::ROOK, color, x, y)
	{
	}

	void Rook::calc_possible_moves(Board *board)
	{
		auto cases = board->get_cases();

		this->explore_direction(1, 0, cases);
		this->explore_direction(-1, 0, cases);
		this->explore_direction(0, 1, cases);
		this->explore_direction(0, -1, cases);
	}
}  // namespace rchess
