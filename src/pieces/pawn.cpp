#include "pieces.hpp"

namespace rchess
{
	Pawn::Pawn(std::string name, PieceColor color, int x, int y) : Piece(name, PieceType::PAWN, color, x, y)
	{
	}

	void Pawn::calc_possible_moves()
	{
		// TODO
	}
}  // namespace rchess
