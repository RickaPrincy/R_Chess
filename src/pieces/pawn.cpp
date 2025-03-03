#include "pieces.hpp"

namespace rchess
{
	Pawn::Pawn(std::string name, PieceColor color, int x, int y) : Piece(name, PieceType::PAWN, color, x, y)
	{
		this->m_increment_value = color == PieceColor::BLACK ? -1 : 1;
	}

	void Pawn::calc_possible_moves(Board &board)
	{
	}
}  // namespace rchess
