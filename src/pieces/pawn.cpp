#include "../board/board.hpp"
#include "../config/config.hpp"
#include "pieces.hpp"

namespace rchess
{
	Pawn::Pawn(std::string name, PieceColor color, int x, int y) : Piece(name, PieceType::PAWN, color, x, y)
	{
		this->m_increment_value = color == PieceColor::BLACK ? -1 : 1;
	}

	void Pawn::calc_possible_moves(Board &board)
	{
		const auto new_y = this->get_y() + this->m_increment_value;
		const auto current_x = this->get_x();

		// y +- 1 move
		if (new_y < config::MAX_COORD && board.is_empty_case(current_x, new_y))
		{
			board.append_or_update_case_valid(this, current_x, new_y);
		}

		// y +- 2 move
		if (this->get_y() == this->m_initial_position.get_y() &&
			board.is_empty_case(current_x, new_y + this->m_increment_value))
		{
			board.append_or_update_case_valid(this, current_x, new_y);
		}
	}
}  // namespace rchess
