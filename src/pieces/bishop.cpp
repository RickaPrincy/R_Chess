#include "pieces.hpp"

namespace rchess
{
	Bishop::Bishop(PieceColor color, int x, int y) : Piece(PieceType::BISHOP, color, x, y)
	{
	}

	void Bishop::calc_possible_moves(Board *board)
	{
		// TODO
	}
}  // namespace rchess
