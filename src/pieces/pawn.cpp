#include "pieces.hpp"

namespace rchess
{
	Pawn::Pawn(PieceColor color, int x, int y) : Piece(PieceType::PAWN, color, x, y)
	{
	}

	void Pawn::calc_possible_moves()
	{
		// TODO
	}
}  // namespace rchess
