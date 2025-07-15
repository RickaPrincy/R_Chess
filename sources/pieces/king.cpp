#include "../board/board.hpp"
#include "pieces.hpp"

namespace rchess
{
	static const std::vector<std::array<int, 2>>
		KING_POSSIBLE_MOVES = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }, { -1, -1 } };

	King::King(PieceColor color, int x, int y) : Piece(PieceType::KING, color, x, y)
	{
	}

	void King::calc_possible_moves(Board *board)
	{
		auto cases = board->get_cases();
		this->explore_moves(KING_POSSIBLE_MOVES, cases);
	}
}  // namespace rchess
