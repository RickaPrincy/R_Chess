#include "../board.hpp"
#include "pieces.hpp"

static const std::vector<std::array<int, 2>>
	KING_POSSIBLE_MOVES = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }, { -1, -1 } };

king::king(piece_color color, int x, int y, std::shared_ptr<sdlk::texture> texture)
	: piece(piece_type::king, color, x, y, std::move(texture), std::move(piece::calc_uv(piece_type::king, color)))
{
}

void king::calc_possible_moves(board *board)
{
	this->explore_moves(KING_POSSIBLE_MOVES, board);
}
