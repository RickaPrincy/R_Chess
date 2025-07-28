#include "../board.hpp"
#include "pieces.hpp"

pawn::pawn(piece_color color, int x, int y, std::shared_ptr<sdlk::texture> texture)
	: piece(piece_type::pawn, color, x, y, std::move(texture), std::move(piece::calc_uv(piece_type::pawn, color)))
{
	this->m_increment_value = color == piece_color::black ? 1 : -1;
}

auto pawn::calc_possible_moves(board *board) -> void
{
	auto squares = board->get_squares();
	int direction = this->m_increment_value;

	// one square forward move
	if (piece::is_valid_position(this->get_x(), this->get_y() + direction))
	{
		auto &forward_case = squares[this->get_x()][this->get_y() + direction];
		if (!forward_case->has_piece())
		{
			forward_case->add_piece_attacker(this);
		}
	}

	// two squares forward move (only if the pawn is on its starting row)
	if ((this->get_color() == piece_color::white && this->get_y() == 6) ||
		(this->get_color() == piece_color::black && this->get_y() == 1))
	{
		if (!squares[this->get_x()][this->get_y() + direction]->has_piece() &&
			!squares[this->get_x()][this->get_y() + 2 * direction]->has_piece())
		{
			auto &two_forward_case = squares[this->get_x()][this->get_y() + 2 * direction];
			two_forward_case->add_piece_attacker(this);
		}
	}

	// capture diagonally left
	if (is_valid_position(this->get_x() - 1, this->get_y() + direction))
	{
		auto &left_diag_case = squares[this->get_x() - 1][this->get_y() + direction];
		if (left_diag_case->has_piece())
		{
			left_diag_case->add_piece_attacker(this);
		}
	}

	// capture diagonally right
	if (is_valid_position(this->get_x() + 1, this->get_y() + direction))
	{
		auto &right_diag_case = squares[this->get_x() + 1][this->get_y() + direction];
		if (right_diag_case->has_piece())
		{
			right_diag_case->add_piece_attacker(this);
		}
	}
}
