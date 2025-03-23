#include "pieces.hpp"

namespace rchess
{
	Queen::Queen(PieceColor color, int x, int y) : Piece(PieceType::QUEEN, color, x, y)
	{
	}

	void Queen::calc_possible_moves(Board &board)
	{
		// TODO
	}
}  // namespace rchess
