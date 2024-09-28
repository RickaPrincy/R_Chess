#include "pieces.hpp"

namespace rchess
{
	Bishop::Bishop(std::string name, PieceColor color, int x, int y) : Piece(name, PieceType::BISHOP, color, x, y)
	{
	}

	void Bishop::calc_possible_moves()
	{
		// TODO
	}
}  // namespace rchess
