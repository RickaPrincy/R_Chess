#include "pieces.hpp"

namespace rchess
{
	Rook::Rook(std::string name, PieceColor color, int x, int y) : Piece(name, PieceType::ROOK, color, x, y)
	{
	}

	void Rook::calc_possible_moves()
	{
		// TODO
	}
}  // namespace rchess
