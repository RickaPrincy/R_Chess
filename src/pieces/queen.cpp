#include "pieces.hpp"

namespace rchess
{
	Queen::Queen(std::string name, PieceColor color, int x, int y) : Piece(name, PieceType::QUEEN, color, x, y)
	{
	}

	void Queen::calc_possible_moves()
	{
		// TODO
	}
}  // namespace rchess
