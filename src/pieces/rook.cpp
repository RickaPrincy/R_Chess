#include "../board/board.hpp"
#include "../constant.hpp"
#include "pieces.hpp"

namespace rchess
{
	using namespace constant;
	Rook::Rook(PieceColor color, int x, int y) : Piece(PieceType::ROOK, color, x, y)
	{
	}

	bool Rook::add_attacker_and_should_stop(int &current_x,
		int &current_y,
		std::array<std::array<std::shared_ptr<Case>, ROW_COUNT>, COLUMN_COUNT> &cases)
	{
		std::shared_ptr<Piece> piece = cases[current_x][current_y]->get_piece();
		cases[current_x][current_y]->add_piece_attacker(this);

		return piece != nullptr;
	}

	void Rook::explore_direction(int dx,
		int dy,
		std::array<std::array<std::shared_ptr<Case>, ROW_COUNT>, COLUMN_COUNT> &cases)
	{
		int current_x = this->get_x() + dx;
		int current_y = this->get_y() + dy;

		while (Piece::is_valid_position(current_x, current_y))
		{
			if (this->add_attacker_and_should_stop(current_x, current_y, cases))
			{
				break;
			}
			current_x += dx;
			current_y += dy;
		}
	}

	void Rook::calc_possible_moves(Board *board)
	{
		auto cases = board->get_cases();

		this->explore_direction(1, 0, cases);
		this->explore_direction(-1, 0, cases);
		this->explore_direction(0, 1, cases);
		this->explore_direction(0, -1, cases);
	}
}  // namespace rchess
