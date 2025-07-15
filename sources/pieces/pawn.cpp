#include "../board/board.hpp"
#include "pieces.hpp"

namespace rchess
{
	Pawn::Pawn(PieceColor color, int x, int y) : Piece(PieceType::PAWN, color, x, y)
	{
		this->m_increment_value = color == PieceColor::BLACK ? 1 : -1;
	}

	void Pawn::calc_possible_moves(Board *board)
	{
		auto cases = board->get_cases();
		int direction = this->m_increment_value;

		// One square forward move
		if (Piece::is_valid_position(this->get_x(), this->get_y() + direction))
		{
			auto &forward_case = cases[this->get_x()][this->get_y() + direction];
			if (!forward_case->has_piece())
			{
				forward_case->add_piece_attacker(this);
			}
		}

		// Two squares forward move (only if the pawn is on its starting row)
		if ((this->get_color() == PieceColor::WHITE && this->get_y() == 6) ||
			(this->get_color() == PieceColor::BLACK && this->get_y() == 1))
		{
			if (!cases[this->get_x()][this->get_y() + direction]->has_piece() &&
				!cases[this->get_x()][this->get_y() + 2 * direction]->has_piece())
			{
				auto &two_forward_case = cases[this->get_x()][this->get_y() + 2 * direction];
				two_forward_case->add_piece_attacker(this);
			}
		}

		// Capture diagonally left
		if (is_valid_position(this->get_x() - 1, this->get_y() + direction))
		{
			auto &left_diag_case = cases[this->get_x() - 1][this->get_y() + direction];
			if (left_diag_case->has_piece())
			{
				left_diag_case->add_piece_attacker(this);
			}
		}

		// Capture diagonally right
		if (is_valid_position(this->get_x() + 1, this->get_y() + direction))
		{
			auto &right_diag_case = cases[this->get_x() + 1][this->get_y() + direction];
			if (right_diag_case->has_piece())
			{
				right_diag_case->add_piece_attacker(this);
			}
		}
	}
}  // namespace rchess
