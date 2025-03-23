#include "../board/board.hpp"
#include "pieces.hpp"

namespace rchess
{
	static const std::vector<std::array<int, 2>> KNIGHT_POSSIBLE_MOVES = { { 2, 1 },
		{ 2, -1 },
		{ -2, 1 },
		{ -2, -1 },
		{ 1, 2 },
		{ 1, -2 },
		{ -1, 2 },
		{ -1, -2 } };

	Knight::Knight(PieceColor color, int x, int y) : Piece(PieceType::KNIGHT, color, x, y)
	{
	}

	void Knight::calc_possible_moves(Board *board)
	{
		auto cases = board->get_cases();
		this->explore_moves(KNIGHT_POSSIBLE_MOVES, cases);
	}
}  // namespace rchess
