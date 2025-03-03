#include "pieces.hpp"

namespace rchess
{
	King::King(std::string name, PieceColor color, int x, int y) : Piece(name, PieceType::KING, color, x, y)
	{
	}

	void King::calc_possible_moves(Board &board)
	{
		// TODO
	}
}  // namespace rchess
