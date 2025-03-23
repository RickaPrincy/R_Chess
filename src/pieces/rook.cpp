#include "pieces.hpp"

namespace rchess
{
	Rook::Rook(PieceColor color, int x, int y) : Piece(PieceType::ROOK, color, x, y)
	{
	}

	void Rook::calc_possible_moves(Board &board)
	{
		// TODO
	}
}  // namespace rchess
