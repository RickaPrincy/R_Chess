#include "pieces.hpp"

namespace rchess
{
	King::King(PieceColor color, int x, int y) : Piece(PieceType::KING, color, x, y)
	{
	}

	void King::calc_possible_moves(Board *board)
	{
		// TODO
	}
}  // namespace rchess
