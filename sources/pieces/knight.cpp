#include "../board.hpp"
#include "pieces.hpp"

static const std::vector<std::array<int, 2>>
	KNIGHT_POSSIBLE_MOVES = { { 2, 1 }, { 2, -1 }, { -2, 1 }, { -2, -1 }, { 1, 2 }, { 1, -2 }, { -1, 2 }, { -1, -2 } };

knight::knight(piece_color color, int x, int y, std::shared_ptr<sdlk::texture> texture)
	: piece(piece_type::knight, color, x, y, std::move(texture), std::move(piece::calc_uv(piece_type::knight, color)))
{
}

void knight::calc_possible_moves(board *board)
{
	this->explore_moves(KNIGHT_POSSIBLE_MOVES, board);
}
