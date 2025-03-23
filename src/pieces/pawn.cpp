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

		int start_x = this->get_x();
		int start_y = this->get_y();

		if (Piece::is_valid_position(start_x, start_y + 1 * direction))
		{
			cases[start_x][start_y + 1 * direction]->add_piece_attacker(this);
		}
	}
}  // namespace rchess
