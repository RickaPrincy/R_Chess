#include "../board.hpp"
#include "pieces.hpp"

rook::rook(piece_color color, int x, int y, std::shared_ptr<sdlk::texture> texture)
	: piece(piece_type::rook, color, x, y, std::move(texture), std::move(piece::calc_uv(piece_type::rook, color)))
{
}

auto rook::calc_possible_moves(board *board) -> void
{
	this->explore_direction(1, 0, board);
	this->explore_direction(-1, 0, board);
	this->explore_direction(0, 1, board);
	this->explore_direction(0, -1, board);
}
