#include "../board.hpp"
#include "pieces.hpp"

bishop::bishop(piece_color color, int x, int y, std::shared_ptr<sdlk::texture> texture)
	: piece(piece_type::bishop, color, x, y, texture, std::move(piece::calc_uv(piece_type::bishop, color)))
{
}

auto bishop::calc_possible_moves(board *board) -> void 
{
	this->explore_direction(1, 1, board);
	this->explore_direction(1, -1, board);
	this->explore_direction(-1, 1, board);
	this->explore_direction(-1, -1, board);
}
