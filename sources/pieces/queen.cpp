#include "../board.hpp"
#include "pieces.hpp"

queen::queen(piece_color color, int x, int y, std::shared_ptr<sdlk::texture> texture)
	: piece(piece_type::queen, color, x, y, std::move(texture), std::move(piece::calc_uv(piece_type::queen, color)))
{
}

void queen::calc_possible_moves(board *board)
{
	// rook-like moves
	this->explore_direction(1, 0, board);
	this->explore_direction(-1, 0, board);
	this->explore_direction(0, 1, board);
	this->explore_direction(0, -1, board);

	// bishop-like moves
	this->explore_direction(1, 1, board);
	this->explore_direction(1, -1, board);
	this->explore_direction(-1, 1, board);
	this->explore_direction(-1, -1, board);
}
