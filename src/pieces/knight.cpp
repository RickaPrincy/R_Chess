#include "pieces.hpp"

namespace rchess
{
	Knight::Knight(PieceColor color, int x, int y) : Piece(PieceType::KNIGHT, color, x, y)
	{
	}

	void Knight::calc_possible_moves(Board &board)
	{
		// TODO
	}
}  // namespace rchess
