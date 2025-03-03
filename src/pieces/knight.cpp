#include "pieces.hpp"

namespace rchess
{
	Knight::Knight(std::string name, PieceColor color, int x, int y) : Piece(name, PieceType::KNIGHT, color, x, y)
	{
	}

	void Knight::calc_possible_moves(Board &board)
	{
		// TODO
	}
}  // namespace rchess
